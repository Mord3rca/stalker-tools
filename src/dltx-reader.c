#include <getopt.h>
#include <stdio.h>

#include "dltx.h"
#include "dynarray.h"


#ifdef DLTX_TRACE
bool write_key_trace(DLTXKey *k, FILE *out) {
	fprintf(
		out, "%8s%-32s = %-32s  ; Defined @%s:%lu\r\n",
		" ", k->name, k->value ? k->value : "", k->file, k->line
	);

	return true;
}

static char sec[512];
bool write_section_trace(DLTXSection *s, FILE *out) {
	snprintf(sec, 512, "[%s]", s->name);
	fprintf(out, "%-77s; Defined @%s:%lu\r\n", sec, s->file, s->line);
	dynarray_foreach(s->keys, (bool (*)(void*, void*))&write_key_trace, out);
	fprintf(out, " \r\n");

	return true;
}
#endif

bool write_key(DLTXKey *k, FILE *out) {
	if (k->value && *(k->value) != 0)
		fprintf(out, "%8s%-32s = %s\r\n", " ", k->name, k->value);
	else
		fprintf(out, "%8s%-32s =\r\n", " ", k->name);

	return true;
}

bool write_section(DLTXSection *s, FILE *out) {
	fprintf(out, "[%s]\r\n", s->name);
	dynarray_foreach(s->keys, (bool (*)(void*, void*))&write_key, out);
	fprintf(out, " \r\n");

	return true;
}

static struct option loptions[] = {
	{"help",	no_argument,	0, 'h'},
#ifdef DLTX_TRACE
	{"trace",	no_argument,	0, 't'},
#endif
	{0,		0,		0,  0 }
};

#ifdef DLTX_TRACE
static char optstring[] = "ht";
#else
static char optstring[] = "h";
#endif

static void print_help(const char *cmd, FILE *out) {
	fprintf(out,
"usage: %s [options] <FILE>\n"
"\nOptions:\n"
"help:		Show this help message\n"
#ifdef DLTX_TRACE
"trace:		Enable trace function & print which file defined the section / variable"
#endif
"\n"
	, cmd);
}

int main(int argc, char *argv[]) {
	int c;
	DLTX *ini;
	DLTX_RETURN_CODE err;
	bool (*write_cb)(DLTXSection*, FILE*) = &write_section;

	while(1) {
		c = getopt_long(argc, argv, optstring, loptions, NULL);

		if (c == -1)
			break;

		switch(c) {
		case 'h':
			print_help(argv[0], stdout);
			return 0;
#ifdef DLTX_TRACE
		case 't':
			write_cb = &write_section_trace;
			break;
#endif
		default:
			print_help(argv[0], stderr);
			return -1;
		}
	}

	if ((argc - optind) != 1) {
		fprintf(stderr, "Error: Missing FILE argument\n");
		print_help(argv[0], stderr);
		return -1;
	}

	if (dltx_init() != NO_ERROR) {
		puts("Failed to init DLTX library");
		return -1;
	}

	ini = dltx_create_from_file(argv[optind], &err);
	if(err != NO_ERROR) {
		puts(dltx_return_code_to_str(err));
		return -err;
	}

	dynarray_foreach(ini->sections, (bool (*)(void*, void*))write_cb, stdout);

	free_dltx(ini);
	dltx_cleanup();
	return 0;
}
