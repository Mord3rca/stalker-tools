#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "ltx.h"
#include "ltx_parser.h"

const size_t ltx_default_key_array_size = 128;
const size_t ltx_default_section_array_size = 32;

const char *ltx_return_code_to_str(LTX_RETURN_CODE err) {
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
	default:
		// Supposed to be dead code .... But we never know !
		return "Dont know";
	}
}

LTX_RETURN_CODE ltx_init(void) {
	return ltx_parser_init();
}

void ltx_cleanup(void) {
	ltx_parser_cleanup();
}

// LTXKey methods

LTXKey *ltx_create_key(const char name[], const char value[]) {
	LTXKey *k = malloc(sizeof(LTXKey));

	k->name = strdup(name);
	k->value = NULL;

	if (value != NULL) {
		k->value = strdup(value);
	}

	return k;
}

void free_ltx_key(LTXKey *k) {
	free(k->name);
	if (k->value != NULL)
		free(k->value);
	free(k);
}

LTXKey *ltx_key_copy(LTXKey *k) {
	LTXKey *r = malloc(sizeof(LTXKey));

	r->name = strdup(k->name);
	r->value = NULL;

	if(k->value)
		r->value = strdup(k->value);

	return r;
}

void ltx_key_set_value(LTXKey *k, const char value[]) {
	if (value == NULL)
		return;

	if (k->value != NULL)
		free(k->value);

	k->value = strdup(value);
}

// LTXSection methods

LTXSection *ltx_create_section(const char name[]) {
	LTXSection *s = malloc(sizeof(LTXSection));

	s->name = strdup(name);

	s->keys = calloc(sizeof(LTXKey), ltx_default_key_array_size);
	s->keys_size = 0;
	s->keys_max_size = ltx_default_key_array_size;

	// Used by LTXReader
	s->inheritance = NULL;

	return s;
}

void free_ltx_section(LTXSection *s) {
	free(s->name);
	if (s->inheritance != NULL)
		free(s->inheritance);

	while(s->keys_size > 0)
		free_ltx_key(s->keys[--(s->keys_size)]);

	free(s->keys);
	free(s);
}

LTXKey *ltx_section_get_key(LTXSection *sec, const char name[]) {
	LTXKey **cur = sec->keys;
	LTXKey **end = sec->keys + sec->keys_size;

	for(;cur < end; cur++) {
		if(strcasecmp((*cur)->name, name) == 0)
			return *cur;
	}

	return NULL;
}

LTX_RETURN_CODE ltx_section_set_key(LTXSection *sec, const char key[], const char value[]) {
	LTXKey *k;
	size_t nsize;

	if (sec->keys_size >= sec->keys_max_size) {
		nsize = sec->keys_max_size + 128;
		sec->keys = reallocarray(sec->keys, sec->keys_max_size, nsize);
		sec->keys_max_size = nsize;
	}

	k = ltx_section_get_key(sec, key);
	if (k == NULL) {
		k = ltx_create_key(key, value);
		sec->keys[sec->keys_size++] = k;
	} else {
		ltx_key_set_value(k, value);
	}


	return NO_ERROR;
}

LTX_RETURN_CODE ltx_section_update_keys(LTXSection *dest, const LTXSection *src) {
	LTXKey *cur, *fnd;
	LTXKey **arr_cur;
	LTXKey **arr_end;

	if (src == NULL)
		return NO_ERROR; // TODO: Null args.

	arr_end = src->keys + src->keys_size;

	for(arr_cur = src->keys; arr_cur < arr_end; arr_cur++) {
		cur = *arr_cur;
		if (cur == NULL)
			break;

		fnd = ltx_section_get_key(dest, cur->name);
		if (fnd != NULL) {
			if (fnd->value != NULL) {
				free(fnd->value);
				fnd->value = NULL;
			}

			if (cur -> value != NULL) {
				fnd->value = strdup(cur->value);
			}
			continue;
		}

		ltx_section_set_key(dest, cur->name, cur->value);
	}
	return NO_ERROR;
}

// LTX Methods

LTX *ltx_create(void) {
	LTX *ltx = malloc(sizeof(LTX));

	ltx->sections = calloc(sizeof(LTXSection*), ltx_default_section_array_size);
	ltx->sections_size = 0;
	ltx->sections_max_size = ltx_default_section_array_size;

	return ltx;
}

void free_ltx(LTX *l) {
	while(l->sections_size > 0)
		free_ltx_section(l->sections[--(l->sections_size)]);
	free(l->sections);
	free(l);
}

LTX *ltx_create_from_file(const char filename[], LTX_RETURN_CODE *err) {
	LTX *r = ltx_create();

	*err = ltx_read_file(r, filename);

	if (*err != NO_ERROR) {
		free_ltx(r);
		r = NULL;
	}

	return r;
}

LTX_RETURN_CODE ltx_read_file(LTX *root, const char filename[]) {
	return ltx_parser_parse_file(root, filename);
}

LTX_RETURN_CODE ltx_read_buffer(LTX *root, char buffer[], size_t buffer_size) {
	return ltx_parser_parse_buffer(root, buffer, buffer_size);
}

LTXSection *ltx_find_section(LTX *root, const char name[]) {
	LTXSection *cur;
	if (!root->sections)
		return NULL;

	for(int i = 0; i < root->sections_size; i++) {
		cur = root->sections[i];
		if (strcasecmp(cur->name, name) == 0)
			return cur;
	}
	return NULL;
}

LTXSection *ltx_create_new_section(LTX *root, const char name[]) {
	size_t nsize;
	LTXSection *s;

	if (root->sections_size >= root->sections_max_size) {
		nsize = root->sections_max_size + 128;
		root->sections = reallocarray(root->sections, root->sections_max_size, nsize);
		root->sections_max_size = nsize;
	}

	s = ltx_create_section(name);
	root->sections[(root->sections_size++)] = s;
	return s;
}


