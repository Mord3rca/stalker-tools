#ifndef _FILESSYTEM_HEADER
#define _FILESSYTEM_HEADER

typedef enum {
	FS_NO_ERROR = 0,
	FS_GLOB_ERROR,
	FS_GLOB_NO_MATCH,

	FS_GENERIC_ERROR,
} fs_return_code;

char *filesystem_path_append(const char[], const char[]);
fs_return_code filesystem_glob(const char[], const char[], char ***);
char *filesystem_get_modfile_glob_path(const char[]);
void filesystem_path_tolower(char[]);

#endif  // _FILESSYTEM_HEADER
