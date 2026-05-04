#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dltx.h"
#include "dynarray.h"
#include "xdb_archive.h"

static const char opts[] = "C:Hxf:hvt";
static const struct option lopts[] = {
	{"directory",	required_argument,	0, 'C'},
	{"show-header",	no_argument,		0, 'H'},
	{"extract",	no_argument,		0, 'x'},
	{"file",	required_argument,	0, 'f'},
	{"help",	no_argument,		0, 'h'},
	{"list",	no_argument,		0, 't'},
	{"verbose",	no_argument,		0, 'v'},
	{0,		0,			0,  0 }
};

static void print_usage(FILE *out, const char *prg) {
	fprintf(out,
"Usage: %s [OPTIONS] ARCHIVE\n\n"
"Options:\n"
"	-C, --directory=DIR:	Use DIR as work directory\n"
"	-H, --show-header:	Print archive LTX header\n"
"	-f, --file=ARCHIVE:	Path to the XDB archive to process\n"
"	-h, --help:		Print help and exit\n"
"	-l, --list:		List archive content\n"
"	-v, --verbose:		Print more infos\n"
"	-x, --extract:		Extract files\n",
prg ? prg : "xdb");
}

static bool verbose = false;
static const char *archive_path = NULL;

static bool print_entry(xdb_metadata_entry *entry, void *_unused) {
	fprintf(stdout, "%s\n", entry->path);
	return true;
}

static bool print_verbose_entry(xdb_metadata_entry *entry, void *_unused) {
	fprintf(
		stdout, "%srw-rw-r-- %6d %s\n",
		entry->ptr == 0 && entry->real_size == 0 ? "d" : "-",
		entry->real_size, entry->path
	);
	return true;
}

static int action_list(xdb *archive) {
	struct dynarray *entries = NULL;

	entries = xdb_read_metadata(archive);
	if (!entries) {
		return 1;
	}

	dynarray_foreach(entries, (bool (*)(void*,void*))(verbose ? &print_verbose_entry : print_entry), NULL);

	free_xdb_metadata(entries);

	return 0;
}

static bool _action_sh_key_iterator(DLTXKey *k, void* _ptr) {
	fprintf(stdout, "%8s%s = %s\n", " ", k->name, k->value);
	return true;
}

static int action_show_header(xdb *archive) {
	DLTX *header;
	DLTXSection *s;

	header = xdb_get_header(archive);
	if (!header) {
		fprintf(stderr, "ERR: Header section not found\n");
		return 1;
	}

	if (header->sections->size != 1) {
		fprintf(stderr, "WARN: Header have more than one section\n");
	}

	s = dltx_find_section(header, "header");
	if (!s) {
		fprintf(stderr, "ERR: Section [header] no found\n");
		return 1;
	}

	fprintf(stdout, "[header]\n");
	dynarray_foreach(s->keys, (bool (*)(void*, void*))&_action_sh_key_iterator, NULL);

	free_dltx(header);
	return 0;
}

static int action_extract(xdb *archive) {
	return xdb_extract_all(archive, "./");
}

int main (int argc, char *argv[]) {
	int c;
	xdb *archive;
	int (*act_cb)(xdb*) = NULL;

	while(1) {
		c = getopt_long(argc, argv, opts, lopts, NULL);
		if (c == -1)
			break;

		switch(c) {
		case 'C':
			if (chdir(optarg) < 0) {
				fprintf(stderr, "ERR: Can't chdir() to %s\n", optarg);
				return 1;
			}
			break;
		case 'H':
			act_cb = &action_show_header;
			break;
		case 'f':
			archive_path = optarg;
			break;
		case 'h':
			print_usage(stdout, argv[0]);
			return 0;
		case 't':
			act_cb = &action_list;
			break;
		case 'v':
			verbose = true;
			break;
		case 'x':
			act_cb = &action_extract;
			break;
		default:
			fprintf(stderr, "ERR: Unknown option code %o\n", c);
			print_usage(stderr, argv[0]);
			return 1;
		}
	}

	if (!act_cb) {
		fprintf(stderr, "ERR: Please choose an action (--extract, --list, --show-header)\n");
		print_usage(stderr, argv[0]);
		return 1;
	}

	if (!archive_path) {
		fprintf(stderr, "ERR: Missing ARCHIVE, use -f option to set it\n");
		print_usage(stderr, argv[0]);
		return 1;
	}

	if (dltx_init() != NO_ERROR) {
		fprintf(stderr, "ERR: failed to init dltx library\n");
		return 1;
	}

	archive = xdb_archive_open(archive_path);
	if (!archive)
		return 1;

	c = act_cb(archive);
	xdb_archive_close(archive);

	return c;
}
