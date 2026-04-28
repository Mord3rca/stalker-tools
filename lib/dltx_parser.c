#include <ctype.h>
#include <limits.h>
#include <regex.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dltx_parser.h"
#include "dynarray.h"
#include "filesystem.h"

const size_t dltx_parser_buffer_size = 256*1024;
const size_t dltx_parser_max_inheritence = 16;

const char dltx_key_regex_pattern[] = "([[:graph:]]*)[[:blank:]]*=[[:blank:]]*(.*)";
const char dltx_include_regex_pattern[] = "#include[[:blank:]]*\"([[:graph:]]*)\"";
const char dltx_section_regex_pattern[] = "([!@]{,2})\\[([[:graph:]]*)\\](:([0-9A-Za-z .,_-]*))?";

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
	DLTX *output;

	DLTX *bases;
	DLTX *results;
	DLTX *overrides;
	DLTX *deletions;

	DLTXSection *cur_section;

	struct dynarray *soverrides;

	size_t cur_line;
	char *cur_file_path;

	DLTX_RETURN_CODE err;

	bool is_parsing_modfile;

	void (*on_error)(DLTXParser*, DLTX_RETURN_CODE, const char*, ...);
	void (*on_new_line)(DLTXParser*, char[]);
	void (*on_new_key)(DLTXParser*, char[], char[]);
	void (*on_include_directive)(DLTXParser*, char[]);
	void (*on_glob_include_directive)(DLTXParser*, char[]);
	void (*on_new_section)(DLTXParser*, char[], char[]);
	void (*on_override_section)(DLTXParser*, OVERRIDE_TYPE, char[], char[]);
	void (*on_deletion_section)(DLTXParser*, char[], char[]);
};

DLTX_RETURN_CODE dltx_parser_process_file(DLTXParser*, const char[]);

static void _dltx_parser_append_inheritance(DLTXSection *s, const char name[]) {
	char **arr = s->inheritance, **n = NULL;
	char **arr_end = arr + dltx_parser_max_inheritence;

	for (;arr < arr_end; arr++) {
		if (! *arr) {
			if(!n)
				n = arr;

			continue;
		}

		if (strcmp(*arr, name) == 0)
			return;  // Already in inheritance
	}

	if (n)
		*n = strdup(name);
}

static void _dltx_parser_delete_inheritance(DLTXSection *s, const char name[]) {
	char **arr = s->inheritance;
	char **arr_end = arr + dltx_parser_max_inheritence;

	for (; arr < arr_end; arr++) {
		if (arr && strcmp(*arr, name)) {
			free(*arr);
			*arr = NULL;
		}
	}
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

	for(i = 0, str = inheritance; ; str = NULL) {
		if (i >= dltx_parser_max_inheritence) {
			root->on_error(root, EVAL_GENERIC_ERROR, "TOO MUCH INHERITANCE ABORT");
			break;
		}
		token = strtok_r(str, ",", &saveptr);
		if (token == NULL)
			break;

		token = _strip(token);
		if (!token)
			continue;

		ar[i] = strdup(token);
		i++;
	}
}


void dltx_parser_default_on_new_section(DLTXParser *root, char name[], char inheritance[]) {
	DLTXSection *s = dltx_find_section(root->bases, name);

	if (s != NULL) {
		root->on_error(root, EVAL_MISSING_SECTION, "Section [%s] exists and override flag is not set", name);
		return;
	}

	s = dltx_create_new_section(root->bases, name);
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
		if (s->keys->size == 0 ) {
			root->on_error(root, EVAL_GENERIC_ERROR, "Section [%s] was marked for deletion twice", name);
			return;
		}

		dltx_section_drop_all_keys(s);
		return;
	}

	dltx_create_new_section(root->deletions, name);
}

static void _dltx_parser_on_delete_key(DLTXParser *root, char key[], char value[]) {
	DLTXSection *s = dltx_find_section(root->deletions, root->cur_section->name);

	if (!s) {
		s = dltx_create_new_section(root->deletions, root->cur_section->name);
		dltx_section_set_key(s, key + 1, NULL);
		return;
	}

	if (s->keys->size == 0)
		return;  // All section marked for deletions, nothing to do

	dltx_section_set_key(s, key + 1, NULL);
}

static void _dltx_parser_on_new_key(DLTXParser *root, char key[], char value[]) {
	dltx_section_set_key(root->cur_section, key, value);

#ifdef DLTX_TRACE
	DLTXKey *k = dltx_section_get_key(root->cur_section, key);
	k->file = root->cur_file_path;
	k->line = root->cur_line;
#endif
}

void dltx_parser_default_on_new_key(DLTXParser *root, char key[], char value[]) {
	if (root->cur_section == NULL) {
		root->on_error(root, PARSER_LOGIC_ERROR, "Cannot insert key into null section");
		return;
	}

	(key[0] == '!' ? _dltx_parser_on_delete_key : _dltx_parser_on_new_key)(root, key, value);
}

void dltx_parser_default_on_include_directive(DLTXParser *root, char path[]) {
	DLTX_RETURN_CODE err;
	char *from = root->cur_file_path;
	char *to = filesystem_path_append(from, path);
	size_t sline = root->cur_line;

	err = dltx_parser_process_file(root, to);
	if (err != NO_ERROR)
		root->on_error(root, FILE_READ_ERROR, "IO error while processing %s", to);
#ifdef DLTX_TRACE
	dynarray_insert(root->bases->files, to);
#else
	free(to);
#endif
	root->cur_file_path = from;
	root->cur_line = sline;
}

void dltx_parser_default_on_glob_include_directive(DLTXParser *root, char path[]) {
	fs_return_code err;
	char **paths = NULL;
	char *to = filesystem_path_append(root->cur_file_path, path);

	err = filesystem_glob(to, root->cur_file_path, &paths);
	if (err != FS_NO_ERROR) {
		if (err != FS_GLOB_NO_MATCH)
			root->on_error(root, FILE_READ_ERROR, "Error while globbing %s", to);
		free(to);
		return;
	}

	for (size_t i = 0; paths[i]; i++) {
		root->on_include_directive(root, paths[i]);
		free(paths[i]);
	}
	free(to);
	free(paths);
}

static bool _is_globbing(const char path[]) {
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

void dltx_parser_default_on_error(DLTXParser *root, DLTX_RETURN_CODE err, const char *format, ...) {
	va_list args;

	fputs("DLTX Parser - ", stderr);
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fputs("\n", stderr);
	root->err = err;
}

DLTXParser *dltx_create_parser() {
	DLTXParser *e = malloc(sizeof(DLTXParser));

	e->bases = dltx_create();
	e->results = dltx_create();
	e->overrides = dltx_create();
	e->deletions = dltx_create();

	e->soverrides = dynarray_create(32);

	e->err = NO_ERROR;

	e->is_parsing_modfile = false;

	e->on_error = dltx_parser_default_on_error;
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
	free_dltx(e->bases);
	free_dltx(e->results);
	free_dltx(e->overrides);
	free_dltx(e->deletions);
	free_dynarray(e->soverrides, NULL);
	free(e);
}

static bool _per_var_deletion(DLTXKey *key, DLTXSection *s) {
	dltx_section_del_key(s, key->name);
	return true;
}

static bool _dltx_apply_overrides_deletions_iterator(DLTXSection *sect, DLTXParser *root) {
	DLTXSection *f;

	// Full deletion case
	if (sect->keys->size == 0) {
		if (
			!dltx_delete_section(root->bases, sect->name) ||
			!dltx_delete_section(root->overrides, sect->name)
		) {
			root->on_error(root,
				(root->output->flags & DLTX_STRICT) ? EVAL_MISSING_SECTION : NO_ERROR,
				"Section [%s] was marked for deletion but do not exist", sect->name
			);
		}
		return root->err == NO_ERROR;
	}

	// per veriable deletion
	f = dltx_find_section(root->bases, sect->name);
	if (f) {
		dynarray_foreach(sect->keys, (bool (*)(void*, void*))&_per_var_deletion, (void*)f);
	}

	f = dltx_find_section(root->overrides, sect->name);
	if (f) {
		dynarray_foreach(sect->keys, (bool (*)(void*, void*))&_per_var_deletion, (void*)f);
	}
	// TODO: Error management if key does not exist at all

	return root->err == NO_ERROR;
}

static bool _dltx_apply_soverrides_create_iterator(char *name, DLTXParser *root) {
	if (dltx_find_section(root->bases, name) == NULL)
		dltx_create_new_section(root->bases, name);

	return true;
}

#ifdef DLTX_TRACE
static bool _merge_files_array(char **obj, struct dynarray *dest) {
	dynarray_insert(dest, obj);
	return true;
}
#endif

static void _dltx_parser_override_inheritance(DLTXSection *base, const DLTXSection *over) {
	char **arr = base->inheritance, **barr;
	char **arr_end = arr + dltx_parser_max_inheritence;

	if (!over->inheritance)
		return;

	if (!base->inheritance) {
		base->inheritance = calloc(sizeof(char*), dltx_parser_max_inheritence);
	        memset(base->inheritance, 0, sizeof(char*) * dltx_parser_max_inheritence);

		barr = base->inheritance;
		arr = over->inheritance;
		arr_end = arr + dltx_parser_max_inheritence;
		for (;arr < arr_end; arr++) {
			if (*arr && **arr == '!')
				continue;

			*barr = strdup(*arr);
			barr++;
		}
		return;
	}

	for (; arr < arr_end; arr++) {
		if (! *arr)
			continue;

		if ((**arr) == '!') {
			_dltx_parser_delete_inheritance(base, (*arr) + 1);
			continue;
		}

		_dltx_parser_append_inheritance(base, *arr);
	}
}

static DLTXSection *_dltx_parser_evaluate_section(DLTXParser*, DLTXSection*, DLTXSection*, int);

static void _dltx_parser_apply_inheritance(DLTXParser *root, DLTXSection *result, const DLTXSection *base, const DLTXSection *over, const int depth) {
	DLTXSection *temp;
	DLTXSection *nbase, *nover;
	char **inheritance = base->inheritance;
	char **inheritance_end = inheritance + dltx_parser_max_inheritence;

	if (!base->inheritance)
		return;

	// Apply inheritance
	for (; inheritance < inheritance_end; inheritance++) {
		if (!(*inheritance))
			continue;

		temp = dltx_find_section(root->results, *inheritance);
		if (!temp) {
			nbase = dltx_find_section(root->bases, *inheritance);
			nover = dltx_find_section(root->overrides, *inheritance);

			if (!nbase) {
				root->on_error(root,
					(root->output->flags & DLTX_STRICT) ? EVAL_GENERIC_ERROR : NO_ERROR,
					"Section [%s] inherits from [%s] but does not exist...", base->name, *inheritance
				);
				if (!nover) {
					nbase = dltx_create_new_section(root->bases, *inheritance);
					dltx_sort(root->bases);
				} else {
					nbase = nover; // Silently use override as base since it is defined
				}
			}

			temp = _dltx_parser_evaluate_section(root, nbase, nover, depth + 1);
		}
		dltx_section_update_keys(result, temp);
	}
}

static DLTXSection *_dltx_parser_evaluate_section(DLTXParser *root, DLTXSection *base, DLTXSection *over, int depth) {
	DLTXSection *result;

	if (depth > 16) {
		root->on_error(root, EVAL_GENERIC_ERROR, "Suspecting cycle deps for section [%s]", base->name);
		return NULL;
	}

	result = dltx_find_section(root->results, base->name);
	if (result)
		return result;

	result = dltx_create_section(base->name);

	if (over)
		_dltx_parser_override_inheritance(base, over);

	_dltx_parser_apply_inheritance(root, result, base, over, depth);

	dltx_section_update_keys(result, base);

	// Apply override
	if (over)
		dltx_section_update_keys(result, over);

#ifdef DLTX_TRACE
	result->file = base->file;
	result->line = base->line;
#endif
	dltx_section_sort(result);
	dynarray_insert(root->results->sections, result);
	return result;
}

static void _dltx_parser_evaluate_all(DLTXParser *root) {
	int result;
	DLTXSection *base, *over;
	DLTXSection **base_cur;
	DLTXSection **override_cur, **override_end;

	base_cur = (DLTXSection**)root->bases->sections->arr;

	override_cur = (DLTXSection**)root->overrides->sections->arr;
	override_end = override_cur + root->overrides->sections->size;

	over = NULL;
	for(base = *base_cur; base_cur < (DLTXSection**)(root->bases->sections->arr + root->bases->sections->size); base=*(++base_cur), over=NULL) {
		//find override
		for (;override_cur < override_end;) {
			over = *override_cur;
			result = strcmp(base->name, over->name);
			if (result > 0) {
				root->on_error(root,
					(root->output->flags & DLTX_STRICT) ? EVAL_MISSING_SECTION : NO_ERROR,
					"Section [%s] don't override anything", over->name
				);
				override_cur++;
				continue;
			} else if (result == 0) {
				// Found it !
				override_cur++;
			} else {
				over = NULL;
			}
			break;
		}

		if (! _dltx_parser_evaluate_section(root, base, over, 0))
			return;

		if (root->err != NO_ERROR)
			return;
	}

	for (; override_cur < override_end; override_cur++) {
		root->on_error(root,
			(root->output->flags & DLTX_STRICT) ? EVAL_MISSING_SECTION : NO_ERROR,
			"Section [%s] don't override anything", (*override_cur)->name
		);
	}

	// Apply resolution to output
	dltx_sort(root->results);
	// TODO: Merge instead of replacing
	free_dynarray(root->output->sections, (void (*)(void*))free_dltx_section);
	root->output->sections = root->results->sections;
	root->results->sections = dynarray_create(1);

	root->output->flags = root->bases->flags;

#ifdef DLTX_TRACE
	if (root->output->files->size > 0) {
		dynarray_foreach(root->results->files, (bool (*)(void*, void*))&_merge_files_array, root->output->files);
		free_dynarray(root->results->files, NULL);
	} else {
		free_dynarray(root->output->files, NULL);
		root->output->files = root->results->files;
	}
	root->results->files = dynarray_create(1);
#endif
}

void _dltx_apply_overrides(DLTXParser *root) {
	// Apply safe overrides
	dynarray_foreach(root->soverrides, (bool (*)(void*, void*))&_dltx_apply_soverrides_create_iterator, root);

	// Apply deletions
	dynarray_foreach(root->deletions->sections, (bool (*)(void*, void*))&_dltx_apply_overrides_deletions_iterator, root);

	dltx_sort(root->bases);
	dltx_sort(root->overrides);

	_dltx_parser_evaluate_all(root);
}

static void _dltx_include_modfile(DLTXParser *root) {
	char *glob;

	if (root->is_parsing_modfile)
		return; // Small guard to avoid modfile chaos

	root->is_parsing_modfile = true;

	glob = filesystem_get_modfile_glob_path(root->cur_file_path);

	root->on_glob_include_directive(root, glob);

	free(glob);
	root->is_parsing_modfile = false;
}

void _dltx_parser_process_buffer(DLTXParser *root, char *buffer, size_t buff_size) {
	char *cur = buffer;
	char *end = buffer + buff_size;
	char *line = buffer;

	while(cur < end) {
		switch(*cur) {
		case '-':
			if (*(cur+1) != '-')
				break;
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

		if (root->err != NO_ERROR)
			return; // If an error occured during parsing, abort.
	}
	_dltx_include_modfile(root);
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
	dynarray_insert(reader->results->files, reader->cur_file_path);
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
	reader->output = dltx;

	err = dltx_parser_process_file(reader, filename);

	if (err == NO_ERROR)
		_dltx_apply_overrides(reader);

	free_dltx_parser(reader);
	return err;
}

void dltx_parser_on_include_noop(DLTXParser *root, char path[]) {
	root->on_error(root, FILE_READ_ERROR, "Inclusion from raw buffer are not yet supported");
}

DLTX_RETURN_CODE dltx_parser_parse_buffer(DLTX *dltx, char buffer[], size_t buffer_size) {
	DLTX_RETURN_CODE err;
	DLTXParser *reader;

	reader = dltx_create_parser();
	reader->output = dltx;

	// Disable file inclusion for raw buffer
	reader->on_include_directive = dltx_parser_on_include_noop;
	reader->on_glob_include_directive = dltx_parser_on_include_noop;

	reader->cur_file_path = strdup("<raw buffer>");
	reader->cur_line = 1;
#ifdef DLTX_TRACE
	// TODO: Can be dupped in case of multiple call of dltx_parser_parse_buffer
	dynarray_insert(reader->results->files, reader->cur_file_path);
#endif

	_dltx_parser_process_buffer(reader, buffer, buffer_size);
	err = reader->err;

	if (err == NO_ERROR)
		_dltx_apply_overrides(reader);

#ifndef DLTX_TRACE
	free(reader->cur_file_path);
#endif
	free_dltx_parser(reader);
	return err;
}
