#include "sterr.h"

stcore_error_code sterr;

void stcore_error_clear(void)
{
	sterr = ST_NO_ERROR;
}

const char *stcore_error_code_str(stcore_error_code err)
{
	switch (err) {
	case ST_NO_ERROR:
		return "No error";

	case ST_FS_FILE_NOT_FOUND:
		return "File not found";

	case ST_FS_GLOB_ERR:
		return "Glob() error";

	case ST_UNKNOWN_ERR:
	default:
		return "Unknown error";
	}
}

const char *stcore_get_last_error_str(void)
{
	return stcore_error_code_str(sterr);
}
