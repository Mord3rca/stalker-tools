#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dltx.h"
#include "dltx_parser.h"

const size_t dltx_default_key_array_size = 128;
const size_t dltx_default_section_array_size = 32;

const char *dltx_return_code_to_str(DLTX_RETURN_CODE err) {
	switch(err) {
	case NO_ERROR:
		return "No error";
		break;

	case FILE_READ_ERROR:
		return "File read error, see errno for more info";
		break;

	case FILE_TOO_BIG:
		return "File too big for buffer size";
		break;

	case INIT_ERROR:
		return "Failure to init";
		break;

	case MISSING_BASE:
		return "An override section did not found its base";
		break;
	default:
		// Supposed to be dead code .... But we never know !
		return "Dont know";
	}
}

DLTX_RETURN_CODE dltx_init(void) {
	return dltx_parser_init();
}

void dltx_cleanup(void) {
	dltx_parser_cleanup();
}

// DLTXKey methods

DLTXKey *dltx_create_key(const char name[], const char value[]) {
	DLTXKey *k = malloc(sizeof(DLTXKey));

	k->name = strdup(name);
	k->value = NULL;

	if (value != NULL) {
		k->value = strdup(value);
	}

#ifdef DLTX_TRACE
	k->file = NULL;
	k->line = -1;
#endif

	return k;
}

void free_dltx_key(DLTXKey *k) {
	free(k->name);
	if (k->value != NULL)
		free(k->value);
	free(k);
}

DLTXKey *dltx_key_copy(DLTXKey *k) {
	DLTXKey *r = malloc(sizeof(DLTXKey));

	r->name = strdup(k->name);
	r->value = NULL;

	if(k->value)
		r->value = strdup(k->value);

#ifdef DLTX_TRACE
	r->file = k->file;
	r->line = k->line;
#endif
	return r;
}

void dltx_key_set_value(DLTXKey *k, const char value[]) {
	if (value == NULL)
		return;

	if (k->value != NULL)
		free(k->value);

	k->value = strdup(value);
}

// DLTXSection methods

DLTXSection *dltx_create_section(const char name[]) {
	DLTXSection *s = malloc(sizeof(DLTXSection));

	s->name = strdup(name);
	for(char *i = s->name; *i != 0; i++)
		*i = tolower(*i);

	s->keys = dynarray_create(dltx_default_key_array_size);

	// Used by DLTXReader
	s->inheritance = NULL;

#ifdef DLTX_TRACE
	s->file = NULL;
	s->line = -1;
#endif

	return s;
}

void free_dltx_section(DLTXSection *s) {
	free(s->name);
	if (s->inheritance != NULL) {
		for (char **i = s->inheritance; i && *i; i++)
			free(*i);
		free(s->inheritance);
	}

	free_dynarray(s->keys, (void (*)(void*))&free_dltx_key);
	free(s);
}

DLTXKey *dltx_section_get_key(DLTXSection *sec, const char name[]) {
	DLTXKey **cur = (DLTXKey**)sec->keys->arr;
	DLTXKey **end = (DLTXKey**)sec->keys->arr + sec->keys->size;

	for(;cur < end; cur++) {
		if(strcmp((*cur)->name, name) == 0)
			return *cur;
	}

	return NULL;
}

DLTX_RETURN_CODE dltx_section_set_key(DLTXSection *sec, const char key[], const char value[]) {
	DLTXKey *k;

	k = dltx_section_get_key(sec, key);
	if (k == NULL) {
		k = dltx_create_key(key, value);
		dynarray_insert(sec->keys, k);
	} else {
		dltx_key_set_value(k, value);
	}


	return NO_ERROR;
}

DLTX_RETURN_CODE dltx_section_del_key(DLTXSection *sec, const char key[]) {
	DLTXKey *k;

	k = dltx_section_get_key(sec, key);
	if (k == NULL)
		return NO_ERROR; // Don't exist, nothing to do

	dynarray_remove(sec->keys, k);
	free_dltx_key(k);
	return NO_ERROR;
}

DLTX_RETURN_CODE dltx_section_update_keys(DLTXSection *dest, const DLTXSection *src) {
	DLTXKey *cur, *fnd;
	DLTXKey **arr_cur;
	DLTXKey **arr_end;

	if (src == NULL)
		return NO_ERROR; // TODO: Null args.

	arr_end = (DLTXKey**)src->keys->arr + src->keys->size;

	for(arr_cur = (DLTXKey**)src->keys->arr; arr_cur < arr_end; arr_cur++) {
		cur = *arr_cur;
		if (cur == NULL)
			break;

		fnd = dltx_section_get_key(dest, cur->name);
		if (fnd != NULL) {
			if (fnd->value != NULL) {
				free(fnd->value);
				fnd->value = NULL;
			}

			if (cur -> value != NULL) {
				fnd->value = strdup(cur->value);
			}
#ifdef DLTX_TRACE
			fnd->file = cur->file;
			fnd->line = cur->line;
#endif
			continue;
		}

		dltx_section_set_key(dest, cur->name, cur->value);
#ifdef DLTX_TRACE
		DLTXKey *k = dltx_section_get_key(dest, cur->name);
		k->file = cur->file;
		k->line = cur->line;
#endif
	}
	return NO_ERROR;
}

// DLTX Methods

DLTX *dltx_create(void) {
	DLTX *dltx = malloc(sizeof(DLTX));

	dltx->sections = dynarray_create(dltx_default_section_array_size);

#ifdef DLTX_TRACE
	dltx->files = dynarray_create(32);
#endif
	return dltx;
}

void free_dltx(DLTX *l) {
	free_dynarray(l->sections, (void (*)(void*))&free_dltx_section);
#ifdef DLTX_TRACE
	free_dynarray(l->files, &free);
#endif
	free(l);
}

DLTX *dltx_create_from_file(const char filename[], DLTX_RETURN_CODE *err) {
	DLTX *r = dltx_create();

	*err = dltx_read_file(r, filename);

	if (*err != NO_ERROR) {
		free_dltx(r);
		r = NULL;
	}

	return r;
}

DLTX_RETURN_CODE dltx_read_file(DLTX *root, const char filename[]) {
	return dltx_parser_parse_file(root, filename);
}

DLTX_RETURN_CODE dltx_read_buffer(DLTX *root, char buffer[], size_t buffer_size) {
	return dltx_parser_parse_buffer(root, buffer, buffer_size);
}

DLTXSection *dltx_find_section(DLTX *root, const char name[]) {
	DLTXSection *cur;
	if (!root->sections)
		return NULL;

	for(int i = 0; i < root->sections->size; i++) {
		cur = root->sections->arr[i];
		if (strcasecmp(cur->name, name) == 0)
			return cur;
	}
	return NULL;
}

DLTXSection *dltx_create_new_section(DLTX *root, const char name[]) {
	DLTXSection *s = dltx_create_section(name);
	dynarray_insert(root->sections, s);

	return s;
}

bool dltx_delete_section(DLTX *root, const char name[]) {
	DLTXSection *s = dltx_find_section(root, name);
	if(!s)
		return false;

	dynarray_remove(root->sections, s);
	free_dltx_section(s);
	return true;
}
