#ifndef _DLTX_HEADER
#define _DLTX_HEADER

#include "dynarray.h"

typedef enum {
	NO_ERROR = 0,
	INIT_ERROR = 1,
	FILE_READ_ERROR,
	FILE_TOO_BIG,
	MISSING_BASE,
} DLTX_RETURN_CODE;

const char *dltx_return_code_to_str(DLTX_RETURN_CODE);

DLTX_RETURN_CODE dltx_init(void);
void dltx_cleanup(void);

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
} DLTX;

/*
 * DLTXKEY methods
 */
DLTXKey *dltx_create_key(const char[], const char[]);
void free_dltx_key(DLTXKey*);

DLTXKey *dltx_key_copy(const DLTXKey*);

void dltx_key_set_value(DLTXKey*, const char[]);
void dltx_key_update(DLTXKey*, const DLTXKey*);

/*
 * DLTXSECTION methods
 */

DLTXSection *dltx_create_section(const char[]);
void free_dltx_section(DLTXSection*);

DLTXKey *dltx_section_get_key(DLTXSection*, const char[]);
DLTX_RETURN_CODE dltx_section_set_key(DLTXSection*, const char[], const char[]);
DLTX_RETURN_CODE dltx_section_del_key(DLTXSection*, const char[]);

DLTX_RETURN_CODE dltx_section_update_key(DLTXSection*, const DLTXKey*);

DLTX_RETURN_CODE dltx_section_update_keys(DLTXSection*, const DLTXSection*);

void dltx_section_sort(DLTXSection*);

/*
 * DLTX methods
 */

DLTX *dltx_create(void);
void free_dltx(DLTX*);

DLTX *dltx_create_from_file(const char[], DLTX_RETURN_CODE*);
DLTX_RETURN_CODE dltx_read_file(DLTX*, const char[]);
DLTX_RETURN_CODE dltx_read_buffer(DLTX*, char[], size_t);

DLTXSection *dltx_find_section(DLTX*, const char[]);
DLTXSection *dltx_create_new_section(DLTX*, const char[]);

bool dltx_delete_section(DLTX*, const char[]);

void dltx_sort(DLTX*);

#endif //_DLTX_HEADER
