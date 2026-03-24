#include <ctype.h>
#include <glob.h>
#include <libgen.h>
#include <limits.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dltx_parser.h"

const size_t dltx_parser_buffer_size = 256*1024;
const size_t dltx_parser_max_inheritence = 8;

const char dltx_key_regex_pattern[] = "([[:graph:]]*)[[:blank:]]*=[[:blank:]]*(.*)";
const char dltx_include_regex_pattern[] = "#include[[:blank:]]*\"([[:graph:]]*)\"";
const char dltx_section_regex_pattern[] = "(!?)\\[([[:graph:]]*)\\](:([[:graph:]]*))?";

regex_t dltx_key_regex;
regex_t dltx_include_regex;
regex_t dltx_section_regex;

char* _rstrip(char *s) {
	char *cur, *end;
	size_t l = strlen(s);

	for(cur = s, end = s + l; cur < end && isspace(*cur); *(cur++) = 0);

	return cur != end ? cur : NULL;
}

char *_lstrip(char *s) {
	char *cur, *end;
	size_t l = strlen(s);

	for(cur = s + l, end = s; cur > end && isspace(*cur); *(cur--) = 0);

	return cur != end ? s : NULL;
}

char *_strip(char *s) {
	s = _rstrip(s);
	if (s)
		_lstrip(s);

	return s;
}

DLTX_RETURN_CODE dltx_parser_init(void) {
	if (regcomp(&dltx_key_regex, dltx_key_regex_pattern, REG_EXTENDED) != 0)
		return INIT_ERROR;

	if (regcomp(&dltx_include_regex, dltx_include_regex_pattern, REG_EXTENDED) != 0)
		return INIT_ERROR;

	if (regcomp(&dltx_section_regex, dltx_section_regex_pattern, REG_EXTENDED) != 0)
		return INIT_ERROR;

	return NO_ERROR;
}

void dltx_parser_cleanup(void) {
	regfree(&dltx_key_regex);
	regfree(&dltx_include_regex);
	regfree(&dltx_section_regex);
}

typedef struct _DLTXParser_s DLTXParser;
struct _DLTXParser_s {
	DLTX *dltx;
	DLTXSection *cur_section;

	size_t cur_line;
	char *cur_file_path;

	void (*on_new_line)(DLTXParser*, char[]);
	void (*on_new_key)(DLTXParser*, char[], char[]);
	void (*on_include_directive)(DLTXParser*, char[]);
	void (*on_glob_include_directive)(DLTXParser*, char[]);
	void (*on_new_section)(DLTXParser*, char[], char[]);
	void (*on_override_section)(DLTXParser*, char[], char[]);
};

DLTX_RETURN_CODE dltx_parser_process_file(DLTXParser*, const char[]);

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

// TODO: Bad naming. Not really a relative resolve
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


void dltx_parser_resolve_inheritance(DLTXParser *root, char inheritance[]) {
	int i;
	DLTXSection *p;
	DLTXSection **ar;
	char *str, *token, *saveptr;

	if (!inheritance || *inheritance == 0)
		return;

	ar = calloc(sizeof(DLTXSection*), dltx_parser_max_inheritence);
	memset(ar, 0, sizeof(DLTXSection*) * dltx_parser_max_inheritence);

	root->cur_section->inheritance = ar;

	for(i = 0, str = inheritance; ; i++, str = NULL) {
		if (i >= dltx_parser_max_inheritence) {
			fprintf(stderr, "TOO MUCH INHERITANCE ABORT\n");
			break;
		}
		token = strtok_r(str, ",", &saveptr);
		if (token == NULL)
			break;

		p = dltx_find_section(root->dltx, token);
		if (p == NULL) {
			fprintf(stderr, "Could not found inheritance (%s) block\n", token);
		}
		dltx_section_update_keys(root->cur_section, p);
		ar[i] = p;
	}
}


void dltx_parser_default_on_new_section(DLTXParser *root, char name[], char inheritance[]) {
	DLTXSection *s = dltx_find_section(root->dltx, name);

	if (s != NULL) {
		fprintf(stderr, "ERROR: Section (%s) exist and overwrite flag is not set\n", name);
		// Should error out
	}

	s = dltx_create_new_section(root->dltx, name);
	root->cur_section = s;

	dltx_parser_resolve_inheritance(root, inheritance);
}

void dltx_parser_default_on_override_section(DLTXParser *root, char name[], char inheritance[]) {
	DLTXSection *s = dltx_find_section(root->dltx, name);

	if (s == NULL) {
		fprintf(stderr, "ERROR: Section (%s) do not exist and overwrite flag is set\n", name);
		// Should error out
	}
	root->cur_section = s;
}

void dltx_parser_default_on_new_key(DLTXParser *root, char key[], char value[]) {
	if (root->cur_section == NULL) {
		fprintf(stderr, "cannot insert key into null section\n");
		return;
	}

	dltx_section_set_key(root->cur_section, key, value);
}

void dltx_parser_default_on_include_directive(DLTXParser *root, char path[]) {
	DLTX_RETURN_CODE err;
	char *from = root->cur_file_path;
	char *to = _relative_to(from, path);
	size_t sline = root->cur_line;

	err = dltx_parser_process_file(root, to);
	if (err != NO_ERROR)
		fprintf(stderr, "IO error for %s\n", to);

	free(to);
	root->cur_file_path = from;
	root->cur_line = sline;
}

void dltx_parser_default_on_glob_include_directive(DLTXParser *root, char path[]) {
	int i;
	glob_t gl;
	char *to = _relative_to(root->cur_file_path, path);
	char *dir = strdup(root->cur_file_path);

	dirname(dir);

	// Not the pretiest but just "works"
	if (glob(to, GLOB_PERIOD, NULL, &gl) != 0) {
		fprintf(stderr, "ERR: Globbing error on %s\n", to);
		free(to);
		return;
	}

	for(i=0; gl.gl_pathv[i]; i++) {
		root->on_include_directive(root, gl.gl_pathv[i] + strlen(dir) + 1);
	}

	free(to);
	free(dir);
	globfree(&gl);
}

bool _is_globbing(const char path[]) {
	const char *start = path;
	const char *end = path + strlen(path);

	// start from the end since most of glob is there.
	while(end > start)
		if( *(--end) == '*')
			return true;
	return false;
}

void dltx_parser_default_process_line(DLTXParser *root, char *line) {
	size_t max_group = 5;  // Based on regex pattern @ beginning of the file
	regmatch_t pmatch[max_group];

	if(*line == '\0')
		return;

	// Avoid blank lines
	line = _strip(line);
	if (line == NULL)
		return;

	if (regexec(&dltx_key_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[1].rm_eo] = 0;
		line[pmatch[2].rm_eo] = 0;
		// Remove trailing spaces / tabs of value
		for(char *c = line + pmatch[2].rm_eo -1; *c == ' ' || *c == '\t'; c--)
			*c = 0;
		root->on_new_key(root, line + pmatch[1].rm_so, line + pmatch[2].rm_so);
		return;
	}

	if (regexec(&dltx_section_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[2].rm_eo] = 0;
		line[pmatch[4].rm_eo] = 0;
		if (pmatch[1].rm_eo == 0)
			root->on_new_section(root, line + pmatch[2].rm_so, line + pmatch[4].rm_so);
		else
			root->on_override_section(root, line + pmatch[2].rm_so, line + pmatch[4].rm_so);

		return;
	}

	if (regexec(&dltx_include_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[1].rm_eo] = 0;
		if (_is_globbing(line + pmatch[1].rm_so))
			root->on_glob_include_directive(root, line + pmatch[1].rm_so);
		else
			root->on_include_directive(root, line + pmatch[1].rm_so);
		return;
	}

	fprintf(stderr, "WARN: (%s:%lu) A non null line was not processed (%s)\n", root->cur_file_path, root->cur_line, line);
}

DLTXParser *dltx_create_parser() {
	DLTXParser *e = malloc(sizeof(DLTXParser));

	e->on_new_key = dltx_parser_default_on_new_key;
	e->on_new_line = dltx_parser_default_process_line;
	e->on_new_section = dltx_parser_default_on_new_section;
	e->on_override_section = dltx_parser_default_on_override_section;
	e->on_include_directive = dltx_parser_default_on_include_directive;
	e->on_glob_include_directive = dltx_parser_default_on_glob_include_directive;

	return e;
}

void _dltx_parser_process_buffer(DLTXParser *root, char *buffer, size_t buff_size) {
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

DLTX_RETURN_CODE dltx_parser_process_file(DLTXParser *reader, const char filename[]) {
	char *buffer;
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		return FILE_READ_ERROR;
	}

	buffer = malloc(dltx_parser_buffer_size);

	fread(buffer, dltx_parser_buffer_size-1, 1, file);
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
	_dltx_parser_process_buffer(reader, buffer, dltx_parser_buffer_size);

	free(buffer);
	free(reader->cur_file_path);
	return NO_ERROR;
}

// Entrypoint
DLTX_RETURN_CODE dltx_parser_parse_file(DLTX *dltx, const char filename[]) {
	DLTXParser *reader;
	DLTX_RETURN_CODE err;

	reader = dltx_create_parser();
	reader->dltx = dltx;

	err = dltx_parser_process_file(reader, filename);

	free(reader);
	return err;
}

void dltx_parser_on_include_noop(DLTXParser *root, char path[]) {
	fprintf(
		stderr, "WARN: (%s:%lu) Inclusion from raw buffer are not yet supported\n",
		root->cur_file_path, root->cur_line
	);
}

DLTX_RETURN_CODE dltx_parser_parse_buffer(DLTX *dltx, char buffer[], size_t buffer_size) {
	DLTXParser *reader;

	reader = dltx_create_parser();
	reader->dltx = dltx;

	// Disable file inclusion for raw buffer
	reader->on_include_directive = dltx_parser_on_include_noop;
	reader->on_glob_include_directive = dltx_parser_on_include_noop;

	reader->cur_file_path = strdup("<raw buffer>");
	reader->cur_line = 1;

	_dltx_parser_process_buffer(reader, buffer, buffer_size);

	free(reader->cur_file_path);
	free(reader);
	return NO_ERROR;
}
