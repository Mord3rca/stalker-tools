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
#include "dynarray.h"

#define DLTX_PARSER_LOG(file, format, ...) fprintf(file, "DLTX Parser - " format "\n", __VA_ARGS__)

#define DLTX_PARSER_LOG_INFO(parser, format, ...) DLTX_PARSER_LOG(stderr, "INFO (in %s:%lu): " format, parser->cur_file_path, parser->cur_line, ##__VA_ARGS__)
#define DLTX_PARSER_LOG_WARN(parser, format, ...) DLTX_PARSER_LOG(stderr, "WARN (in %s:%lu): " format, parser->cur_file_path, parser->cur_line, ##__VA_ARGS__)
#define DLTX_PARSER_LOG_ERR(parser, format, ...)  DLTX_PARSER_LOG(stderr, "ERR (in %s:%lu):  " format, parser->cur_file_path, parser->cur_line, ##__VA_ARGS__)
#define DLTX_PARSER_LOG_DBG(parser, format, ...)  DLTX_PARSER_LOG(stderr, "DBG (in %s:%lu):  " format, parser->cur_file_path, parser->cur_line, ##__VA_ARGS__)

const size_t dltx_parser_buffer_size = 256*1024;
const size_t dltx_parser_max_inheritence = 8;

const char dltx_key_regex_pattern[] = "([[:graph:]]*)[[:blank:]]*=[[:blank:]]*(.*)";
const char dltx_include_regex_pattern[] = "#include[[:blank:]]*\"([[:graph:]]*)\"";
const char dltx_section_regex_pattern[] = "([!@]{,2})\\[([[:graph:]]*)\\](:([[:graph:]]*))?";

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
	size_t l = strlen(s) - 1;

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

typedef enum {
	OVERRIDE,
	OVERRIDE_SAFE,
	OVERRIDE_DELETE,

	OVERRIDE_NONE,
} OVERRIDE_TYPE;

static OVERRIDE_TYPE _char_to_override_enum(const char modifier[2] /* Assuming min size of 2 */) {
	switch (modifier[0]) {
	case '!':
		return modifier[1] == '!' ? OVERRIDE_DELETE : OVERRIDE;
		;;
	case '@':
		return OVERRIDE_SAFE;
		;;
	default:
		return OVERRIDE_NONE;
	}
}

typedef struct _DLTXParser_s DLTXParser;
struct _DLTXParser_s {
	DLTX *dltx;
	DLTX *overrides;
	DLTX *deletions;

	DLTXSection *cur_section;

	struct dynarray *soverrides;

	size_t cur_line;
	char *cur_file_path;

	DLTX_RETURN_CODE err;

	void (*on_new_line)(DLTXParser*, char[]);
	void (*on_new_key)(DLTXParser*, char[], char[]);
	void (*on_include_directive)(DLTXParser*, char[]);
	void (*on_glob_include_directive)(DLTXParser*, char[]);
	void (*on_new_section)(DLTXParser*, char[], char[]);
	void (*on_override_section)(DLTXParser*, OVERRIDE_TYPE, char[], char[]);
	void (*on_deletion_section)(DLTXParser*, char[], char[]);
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


static void dltx_parser_parse_inheritance(DLTXParser *root, char inheritance[]) {
	int i;
	char **ar;
	char *str, *token, *saveptr;

	if (!inheritance || *inheritance == 0)
		return;

	ar = calloc(sizeof(char*), dltx_parser_max_inheritence);
	memset(ar, 0, sizeof(char*) * dltx_parser_max_inheritence);

	root->cur_section->inheritance = ar;

	for(i = 0, str = inheritance; ; i++, str = NULL) {
		if (i >= dltx_parser_max_inheritence) {
			DLTX_PARSER_LOG_ERR(root, "TOO MUCH INHERITANCE ABORT");
			break;
		}
		token = strtok_r(str, ",", &saveptr);
		if (token == NULL)
			break;

		ar[i] = strdup(token);
	}
}


void dltx_parser_default_on_new_section(DLTXParser *root, char name[], char inheritance[]) {
	DLTXSection *s = dltx_find_section(root->dltx, name);

	if (s != NULL) {
		DLTX_PARSER_LOG_ERR(root, "Section [%s] exists and override flag is not set", name);
		// Should error out
	}

	s = dltx_create_new_section(root->dltx, name);
#ifdef DLTX_TRACE
	s->file = root->cur_file_path;
	s->line = root->cur_line;
#endif
	root->cur_section = s;

	dltx_parser_parse_inheritance(root, inheritance);
}

void dltx_parser_default_on_override_section(DLTXParser *root, OVERRIDE_TYPE otype, char name[], char inheritance[]) {
	DLTXSection *s = dltx_find_section(root->overrides, name);

	if (s == NULL) {
		s = dltx_create_new_section(root->overrides, name);
#ifdef DLTX_TRACE
		s->file = root->cur_file_path;
		s->line = root->cur_line;
#endif
	}

	if (otype == OVERRIDE_SAFE)
		dynarray_insert(root->soverrides, s->name);

	root->cur_section = s;
}

void dltx_parser_default_on_deletion_section(DLTXParser *root, char name[], char inheritance[]) {
	DLTXSection *s = dltx_find_section(root->deletions, name);

	if (s) {
		DLTX_PARSER_LOG_WARN(root, "Section [%s] was marked for deletion twice", name);
		return;
	}

	dltx_create_new_section(root->deletions, name);
}

void dltx_parser_default_on_new_key(DLTXParser *root, char key[], char value[]) {
	if (root->cur_section == NULL) {
		DLTX_PARSER_LOG_ERR(root, "Cannot insert key into null section");
		return;
	}

	dltx_section_set_key(root->cur_section, key, value);
#ifdef DLTX_TRACE
	DLTXKey *k = dltx_section_get_key(root->cur_section, key);
	k->file = root->cur_file_path;
	k->line = root->cur_line;
#endif
}

void dltx_parser_default_on_include_directive(DLTXParser *root, char path[]) {
	DLTX_RETURN_CODE err;
	char *from = root->cur_file_path;
	char *to = _relative_to(from, path);
	size_t sline = root->cur_line;

	err = dltx_parser_process_file(root, to);
	if (err != NO_ERROR)
		DLTX_PARSER_LOG_ERR(root, "IO error");
#ifdef DLTX_TRACE
	dynarray_insert(root->dltx->files, to);
#else
	free(to);
#endif
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
		DLTX_PARSER_LOG_ERR(root, "Globbing error");
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
	char *inheritance;
	OVERRIDE_TYPE otype;
	size_t max_group = 5;  // Based on regex pattern @ beginning of the file
	regmatch_t pmatch[max_group];

	if(*line == '\0')
		return;

	// Avoid blank lines
	line = _strip(line);
	if (line == NULL)
		return;

	// Start with a # so probably a header
	if (line[0] == '#' && regexec(&dltx_include_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[1].rm_eo] = 0;
		if (_is_globbing(line + pmatch[1].rm_so))
			root->on_glob_include_directive(root, line + pmatch[1].rm_so);
		else
			root->on_include_directive(root, line + pmatch[1].rm_so);
		return;
	}

	// Key with assignation
	if (regexec(&dltx_key_regex, line, max_group, pmatch, 0) == 0) {
		line[pmatch[1].rm_eo] = 0;
		line[pmatch[2].rm_eo] = 0;
		root->on_new_key(root, line + pmatch[1].rm_so, line + pmatch[2].rm_so);
		return;
	}

	if (regexec(&dltx_section_regex, line, max_group, pmatch, 0) == 0) {
		inheritance = NULL;
		line[pmatch[2].rm_eo] = 0;

		// Check if inheritance matched
		if (pmatch[4].rm_eo > -1) {
			inheritance = line + pmatch[4].rm_so;
			line[pmatch[4].rm_eo] = 0;
		}

		otype = _char_to_override_enum(line + pmatch[1].rm_so);
		switch(otype) {
		case OVERRIDE:
		case OVERRIDE_SAFE:
			root->on_override_section(root, otype, line + pmatch[2].rm_so, inheritance);
			break;
		case OVERRIDE_DELETE:
			root->on_deletion_section(root, line + pmatch[2].rm_so, inheritance);
			break;
		default:
			root->on_new_section(root, line + pmatch[2].rm_so, inheritance);
		}
		return;
	}

	// Well, if it's nothing. It should be a key
	root->on_new_key(root, line, NULL);
}

DLTXParser *dltx_create_parser() {
	DLTXParser *e = malloc(sizeof(DLTXParser));

	e->overrides = dltx_create();
	e->deletions = dltx_create();

	e->soverrides = dynarray_create(32);

	e->err = NO_ERROR;

	e->on_new_key = dltx_parser_default_on_new_key;
	e->on_new_line = dltx_parser_default_process_line;
	e->on_new_section = dltx_parser_default_on_new_section;
	e->on_override_section = dltx_parser_default_on_override_section;
	e->on_deletion_section = dltx_parser_default_on_deletion_section;
	e->on_include_directive = dltx_parser_default_on_include_directive;
	e->on_glob_include_directive = dltx_parser_default_on_glob_include_directive;

	return e;
}

void free_dltx_parser(DLTXParser *e) {
	free_dltx(e->overrides);
	free_dltx(e->deletions);
	free_dynarray(e->soverrides, NULL);
	free(e);
}

static bool _dltx_apply_overrides_deletions_iterator(DLTXSection *sect, DLTXParser *root) {
	if (
		!dltx_delete_section(root->dltx, sect->name) ||
		!dltx_delete_section(root->overrides, sect->name)
	) {
		DLTX_PARSER_LOG_WARN(root, "Section [%s] was marked for deletion but do not exist", sect->name);
	}

	return true;
}

static bool _dltx_apply_soverrides_create_iterator(char *name, DLTXParser *root) {
	if (dltx_find_section(root->dltx, name) == NULL)
		dltx_create_new_section(root->dltx, name);

	return true;
}

// TODO: Suboptimal ... But will do for now.
static bool _dltx_verify_overrides(DLTXSection *s, DLTXParser *root) {
	if (dltx_find_section(root->dltx, s->name) == NULL) {
		DLTX_PARSER_LOG_ERR(root, "Section [%s] don't override anything", s->name);
		root->err = MISSING_BASE;
		return false;
	}

	return true;
}

static bool _is_in_immutable(const char name[], const char *immutable[]) {
	const char **cur;

	for (cur = immutable; cur && *cur; cur++)
		if (strcmp(name, *cur) == 0)
			return true;

	return false;
}

DLTX_RETURN_CODE _dltx_update_some_keys(DLTXSection *dest, const DLTXSection *src, const char *immutable[]) {
	DLTXKey **arr_cur = (DLTXKey**)src->keys->arr;
	DLTXKey **arr_end = (DLTXKey**)src->keys->arr + src->keys->size;

	for (; arr_cur < arr_end; arr_cur++) {
		if (_is_in_immutable((*arr_cur)->name, immutable))
			continue;

		// TODO: Losing TRACE information....
		dltx_section_set_key(dest, (*arr_cur)->name, (*arr_cur)->value);
	}

	return NO_ERROR;
}

static bool _dltx_resolve_section_iterator(DLTXSection *base, DLTXParser *root) {
	DLTXSection *temp;
	char **inheritance;
	const char *immutable[base->keys->size+1];

	immutable[base->keys->size] = 0;
	for (size_t i = 0; i < base->keys->size; i++) {
		immutable[i] = ((DLTXKey*)base->keys->arr[i])->name;
	}

	// Apply inheritance
	for (inheritance = base->inheritance; inheritance && *inheritance; inheritance++) {
		temp = dltx_find_section(root->dltx, *inheritance);
		if (!temp) {
			root->err = MISSING_BASE;
			DLTX_PARSER_LOG_ERR(root, "Section [%s] could not inherit %s", base->name, *inheritance);
			return false;
		}
		_dltx_update_some_keys(base, temp, immutable);
	}

	temp = dltx_find_section(root->overrides, base->name);
	if (temp)
		dltx_section_update_keys(base, temp);

	return true;
}

void _dltx_apply_overrides(DLTXParser *root) {
	// Apply safe overrides
	dynarray_foreach(root->soverrides, (bool (*)(void*, void*))&_dltx_apply_soverrides_create_iterator, root);

	// Apply deletions
	dynarray_foreach(root->deletions->sections, (bool (*)(void*, void*))&_dltx_apply_overrides_deletions_iterator, root);

	// Smol verification
	dynarray_foreach(root->overrides->sections, (bool (*)(void*, void*))&_dltx_verify_overrides, root);
	if (root->err != NO_ERROR)
		return;  // Abort

	dynarray_foreach(root->dltx->sections, (bool (*)(void*, void*))&_dltx_resolve_section_iterator, root);
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
			break;
		}
	}

	_dltx_apply_overrides(root);
}

DLTX_RETURN_CODE dltx_parser_process_file(DLTXParser *reader, const char filename[]) {
	char *buffer;
	FILE *file = fopen(filename, "r");
	DLTX_RETURN_CODE err;

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
#ifdef DLTX_TRACE
	dynarray_insert(reader->dltx->files, reader->cur_file_path);
#endif
	// Processing loop
	_dltx_parser_process_buffer(reader, buffer, dltx_parser_buffer_size);
	err = reader->err;

	free(buffer);
#ifndef DLTX_TRACE
	free(reader->cur_file_path);
#endif
	return err;
}

// Entrypoint
DLTX_RETURN_CODE dltx_parser_parse_file(DLTX *dltx, const char filename[]) {
	DLTXParser *reader;
	DLTX_RETURN_CODE err;

	reader = dltx_create_parser();
	reader->dltx = dltx;

	err = dltx_parser_process_file(reader, filename);

	free_dltx_parser(reader);
	return err;
}

void dltx_parser_on_include_noop(DLTXParser *root, char path[]) {
	DLTX_PARSER_LOG_WARN(root, "Inclusion from raw buffer are not yet supported");
}

DLTX_RETURN_CODE dltx_parser_parse_buffer(DLTX *dltx, char buffer[], size_t buffer_size) {
	DLTX_RETURN_CODE err;
	DLTXParser *reader;

	reader = dltx_create_parser();
	reader->dltx = dltx;

	// Disable file inclusion for raw buffer
	reader->on_include_directive = dltx_parser_on_include_noop;
	reader->on_glob_include_directive = dltx_parser_on_include_noop;

	reader->cur_file_path = strdup("<raw buffer>");
	reader->cur_line = 1;
#ifdef DLTX_TRACE
	// TODO: Can be dupped in case of multiple call of dltx_parser_parse_buffer
	dynarray_insert(reader->dltx->files, reader->cur_file_path);
#endif

	_dltx_parser_process_buffer(reader, buffer, buffer_size);
	err = reader->err;

#ifndef DLTX_TRACE
	free(reader->cur_file_path);
#endif
	free_dltx_parser(reader);
	return err;
}
