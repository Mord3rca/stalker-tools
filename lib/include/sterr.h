#ifndef _STCORE_ERR_HEADER
#define _STCORE_ERR_HEADER

typedef enum {
	ST_NO_ERROR = 0,

	// STCore FS
	ST_FS_FILE_NOT_FOUND,
	ST_FS_GLOB_ERR,

	ST_UNKNOWN_ERR,
} stcore_error_code;

extern stcore_error_code sterr;

void stcore_error_clear(void);
const char *stcore_error_code_str(stcore_error_code err);
const char *stcore_get_last_error_str(void);

#endif // _STCORE_ERR_HEADER
