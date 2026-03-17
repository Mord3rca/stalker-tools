#include <libgen.h>
#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ltx_reader.h"

const size_t ltx_reader_buffer_size = 256*1024;
const size_t ltx_reader_max_inheritence = 8;

const char ltx_key_regex_pattern[] = "[[:blank:]]*([[:graph:]]*)[[:blank:]]*=[[:blank:]]*(.*)";
const char ltx_include_regex_pattern[] = "#include[[:blank:]]*\"([[:graph:]]*)\"";
const char ltx_section_regex_pattern[] = "[[:blank:]]*(!?)\\[([[:graph:]]*)\\](:([[:graph:]]*))?";

regex_t ltx_key_regex;
regex_t ltx_include_regex;
regex_t ltx_section_regex;

LTX_RETURN_CODE ltx_reader_init(void) {
	if (regcomp(&ltx_key_regex, ltx_key_regex_pattern, REG_EXTENDED) != 0)
		return INIT_ERROR;

	if (regcomp(&ltx_include_regex, ltx_include_regex_pattern, REG_EXTENDED) != 0)
		return INIT_ERROR;

	if (regcomp(&ltx_section_regex, ltx_section_regex_pattern, REG_EXTENDED) != 0)
		return INIT_ERROR;

	return NO_ERROR;
}

void ltx_reader_cleanup(void) {
	regfree(&ltx_key_regex);
	regfree(&ltx_include_regex);
	regfree(&ltx_section_regex);
}

typedef struct _LTXReader_s LTXReader;
struct _LTXReader_s {
	LTX *ltx;
	LTXSection *cur_section;

	size_t cur_line;
	char *cur_file_path;

	void (*on_new_line)(LTXReader*, char[]);
	void (*on_new_key)(LTXReader*, char[], char[]);
	void (*on_include_directive)(LTXReader*, char[]);
	void (*on_new_section)(LTXReader*, char[], char[], char[]);
};

LTX_RETURN_CODE ltx_reader_process_file(LTXReader*, const char[]);

void _to_unix_path(char path[]) {
	char *cur = path;

	if (!cur)
		return;

	while(*cur != 0) {
		if (*cur == '\\')
			*cur = '/';
		cur++;
	}
}

char *_relative_to(const char *path, const char *file) {
	char *r = calloc(sizeof(char), PATH_MAX);
	char *p = strdup(path);

	memset(r, 0, PATH_MAX);

	strcpy(r, dirname(p));
	free(p);

	strcat(r, "/");
	strcat(r, file);
	_to_unix_path(r);  // Fix path in case of *NIX
	return r;
}


void ltx_reader_resolve_inheritance(LTXReader *root, char inheritance[]) {
	int i;
	LTXSection *p;
	LTXSection **ar;
	char *str, *token, *saveptr;

	if (!inheritance || *inheritance == 0)
		return;

	ar = calloc(sizeof(LTXSection*), ltx_reader_max_inheritence);
	memset(ar, 0, sizeof(LTXSection*) * ltx_reader_max_inheritence);

	root->cur_section->inheritance = ar;

	for(i = 0, str = inheritance; ; i++, str = NULL) {
		if (i >= ltx_reader_max_inheritence) {
			fprintf(stderr, "TOO MUCH INHERITANCE ABORT\n");
			break;
		}
		token = strtok_r(str, ",", &saveptr);
		if (token == NULL)
			break;

		p = ltx_find_section(root->ltx, token);
		if (p == NULL) {
			fprintf(stderr, "Could not found inheritance (%s) block\n", token);
		}
		ltx_section_update_keys(root->cur_section, p);
		ar[i] = p;
	}
}


void ltx_reader_default_on_new_section(LTXReader *root, char unused[], char name[], char inheritance[]) {
	LTXSection *s = ltx_create_new_section(root->ltx, name);
	root->cur_section = s;

	// TODO unused is override flag
	ltx_reader_resolve_inheritance(root, inheritance);
}

void ltx_reader_default_on_new_key(LTXReader *root, char key[], char value[]) {
	if (root->cur_section == NULL) {
		fprintf(stderr, "cannot insert key into null section\n");
		return;
	}

	ltx_section_set_key(root->cur_section, key, value);
}

void ltx_reader_default_on_include_directive(LTXReader *root, char path[]) {
	LTX_RETURN_CODE err;
	char *from = root->cur_file_path;
	char *to = _relative_to(from, path);
	size_t sline = root->cur_line;

	//err = ltx_read_file(root, to); // TODO
	err = ltx_reader_process_file(root, to);
	if (err != NO_ERROR)
		fprintf(stderr, "IO error for %s\n", to);

	free(to);
	root->cur_file_path = from;
	root->cur_line = sline;
}

void ltx_reader_default_process_line(LTXReader *root, char *line) {
	size_t max_group = 5;  // Based on regex pattern @ beginning of the file
	regmatch_t pmatch[max_group];

	if(*line == '\0')
		return;

	if (regexec(&ltx_key_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[1].rm_eo] = 0;
		line[pmatch[2].rm_eo] = 0;
		// Remove trailing spaces / tabs of value
		for(char *c = line + pmatch[2].rm_eo -1; *c == ' ' || *c == '\t'; c--)
			*c = 0;
		root->on_new_key(root, line + pmatch[1].rm_so, line + pmatch[2].rm_so);
		return;
	}

	if (regexec(&ltx_section_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[2].rm_eo] = 0;
		line[pmatch[4].rm_eo] = 0;
		root->on_new_section(root, NULL, line + pmatch[2].rm_so, line + pmatch[4].rm_so);
		return;
	}

	if (regexec(&ltx_include_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[1].rm_eo] = 0;
		root->on_include_directive(root, line + pmatch[1].rm_so);
		return;
	}

	fprintf(stderr, "WARN: (%s:%lu) A non null line was not processed (%s)\n", root->cur_file_path, root->cur_line, line);
}

LTXReader *ltx_create_reader() {
	LTXReader *e = malloc(sizeof(LTXReader));

	e->on_new_key = ltx_reader_default_on_new_key;
	e->on_new_line = ltx_reader_default_process_line;
	e->on_new_section = ltx_reader_default_on_new_section;
	e->on_include_directive = ltx_reader_default_on_include_directive;

	return e;
}

void _ltx_reader_process_buffer(LTXReader *root, char *buffer, size_t buff_size) {
	char *cur = buffer;
	char *end = buffer + buff_size;
	char *line = buffer;

	while(cur < end) {
		switch(*cur) {
		case ';':
		case '\r':
			*cur = '\0';
			break;
		case '\n':
			*cur = '\0';
			root->on_new_line(root, line);
			line = cur+1;
			root->cur_line++;
			break;
		default:
		}

		cur++;

		if(*cur == '\0') {
			root->on_new_line(root, line);
			return;
		}
	}
}

LTX_RETURN_CODE ltx_reader_process_file(LTXReader *reader, const char filename[]) {
	char *buffer;
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		return FILE_READ_ERROR;
	}

	buffer = malloc(ltx_reader_buffer_size);

	fread(buffer, ltx_reader_buffer_size-1, 1, file);
	buffer[ftell(file)] = 0;

	if(feof(file) == 0) {
		free(buffer);
		fclose(file);
		return FILE_TOO_BIG;
	}
	fclose(file);

	reader->cur_file_path = strdup(filename);
	reader->cur_line = 1;
	// Processing loop
	_ltx_reader_process_buffer(reader, buffer, ltx_reader_buffer_size);

	free(buffer);
	return NO_ERROR;
}

// Entrypoint
LTX_RETURN_CODE ltx_reader_parse_file(LTX *ltx, const char filename[]) {
	LTXReader *reader;
	LTX_RETURN_CODE err;

	reader = ltx_create_reader();
	reader->ltx = ltx;

	err = ltx_reader_process_file(reader, filename);

	free(reader);
	return err;
}
