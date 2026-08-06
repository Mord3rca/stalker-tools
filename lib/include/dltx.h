#ifndef _DLTX_HEADER
#define _DLTX_HEADER

#include <stdio.h>

#include "dynarray.h"

#define DLTX_READONLY	(1 << 0)
#define DLTX_SORTED	(1 << 1)
#define DLTX_STRICT	(1 << 2)

typedef enum {
	NO_ERROR = 0,
	INIT_ERROR = 1,
	FILE_READ_ERROR,
	FILE_TOO_BIG,

	PARSER_FORMAT_ERROR,
	PARSER_LOGIC_ERROR,

	EVAL_GENERIC_ERROR,
	EVAL_MISSING_SECTION,
} DLTX_RETURN_CODE;

const char *dltx_return_code_to_str(DLTX_RETURN_CODE err);

extern DLTX_RETURN_CODE dltx_init_code;

typedef struct {
	char *name;
	char *value;

#ifdef DLTX_TRACE
	char *file;
	size_t line;
#endif
} DLTXKey;

typedef struct _DLTXSection_s DLTXSection;
struct _DLTXSection_s {
	char *name;

	// A null terminated array since inheritance are limited
	char **inheritance;

	struct dynarray *keys;

#ifdef DLTX_TRACE
	char *file;
	size_t line;
#endif
};

typedef struct {
	struct dynarray *sections;

#ifdef DLTX_TRACE
	struct dynarray *files;
#endif

	int flags;
} DLTX;

/*
 * DLTXKEY methods
 */
DLTXKey *dltx_create_key(const char name[], const char value[]);
void free_dltx_key(DLTXKey *k);

DLTXKey *dltx_key_copy(const DLTXKey *k);

void dltx_key_set_value(DLTXKey *k, const char value[]);
void dltx_key_update(DLTXKey *dest, const DLTXKey *src);

/*
 * DLTXSECTION methods
 */

DLTXSection *dltx_create_section(const char name[]);
void free_dltx_section(DLTXSection *s);

DLTXKey *dltx_section_get_key(DLTXSection *sec, const char name[]);
DLTX_RETURN_CODE dltx_section_set_key(DLTXSection *sec, const char key[], const char value[]);
DLTX_RETURN_CODE dltx_section_del_key(DLTXSection *sec, const char key[]);

DLTX_RETURN_CODE dltx_section_drop_all_keys(DLTXSection *sec);

DLTX_RETURN_CODE dltx_section_update_key(DLTXSection *sec, const DLTXKey *src);

DLTX_RETURN_CODE dltx_section_update_keys(DLTXSection *sec, const DLTXSection *src);

void dltx_section_sort(DLTXSection *s);

/*
 * DLTX methods
 */

DLTX *dltx_create(void);
void free_dltx(DLTX *l);

DLTX *dltx_create_from_file(const char filename[], DLTX_RETURN_CODE *err);
DLTX_RETURN_CODE dltx_read_file(DLTX *root, const char filename[]);
DLTX_RETURN_CODE dltx_read_buffer(DLTX *root, char buffer[], size_t buffer_size);

DLTXSection *dltx_find_section(DLTX *root, const char name[]);
DLTXSection *dltx_create_new_section(DLTX *root, const char name[]);

const char *dltx_get_key(DLTX *root, const char section[], const char key[]);

bool dltx_delete_section(DLTX *root, const char name[]);

void dltx_set_readonly(DLTX *root, bool ro);
void dltx_set_strict_mode(DLTX *root, bool strict);

void dltx_sort(DLTX *root);

int dltx_save_to_file(DLTX *root, FILE *out);

#endif //_DLTX_HEADER
