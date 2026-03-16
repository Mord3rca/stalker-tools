#ifndef _LTX_HEADER
#define _LTX_HEADER

typedef enum {
	NO_ERROR = 0,
	INIT_ERROR = 1,
	FILE_READ_ERROR,
	FILE_TOO_BIG,
} LTX_RETURN_CODE;

const char *ltx_return_code_to_str(LTX_RETURN_CODE);

LTX_RETURN_CODE ltx_init(void);
void ltx_cleanup(void);

typedef struct {
	char *name;
	char *value;
} LTXKey;

typedef struct _LTXSection_s LTXSection;
struct _LTXSection_s {
	char *name;

	// A null terminated array since inheritance are limited
	LTXSection **inheritance;

	size_t keys_size;
	size_t keys_max_size;
	LTXKey **keys;
};

typedef struct {
	size_t sections_size;
	size_t sections_max_size;
	LTXSection **sections;
} LTX;

/*
 * LTXKEY methods
 */
LTXKey *ltx_create_key(const char[], const char[]);
void free_ltx_key(LTXKey*);

LTXKey *ltx_key_copy(LTXKey*);

/*
 * LTXSECTION methods
 */

LTXSection *ltx_create_section(const char[]);
void free_ltx_section(LTXSection*);

LTXKey *ltx_section_get_key(LTXSection*, const char[]);
LTX_RETURN_CODE ltx_section_set_key(LTXSection*, const char[], const char[]);

LTX_RETURN_CODE ltx_section_update_keys(LTXSection*, const LTXSection*);

/*
 * LTX methods
 */

LTX *ltx_create(void);
void free_ltx(LTX*);

LTX *ltx_create_from_file(const char[], LTX_RETURN_CODE*);
LTX_RETURN_CODE ltx_read_file(LTX*, const char[]);

LTXSection *ltx_find_section(LTX*, const char[]);
LTXSection *ltx_create_new_section(LTX*, const char[]);

#endif //_LTX_HEADER
