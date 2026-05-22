#ifndef _FILESSYTEM_HEADER
#define _FILESSYTEM_HEADER

typedef enum {
	FS_NO_ERROR = 0,
	FS_GLOB_ERROR,
	FS_GLOB_NO_MATCH,

	FS_GENERIC_ERROR,
} fs_return_code;

int  filesystem_init(void);
void filesystem_cleanup(void);

char *filesystem_path_append(const char[], const char[]);
fs_return_code filesystem_glob(const char[], const char[], char ***);
char *filesystem_get_modfile_glob_path(const char[]);
void filesystem_path_tolower(char[]);

void filesystem_to_system_path(char[]);

int filesystem_create_directory(const char[]);

char *filesystem_resolve_path(const char[]);

#endif  // _FILESSYTEM_HEADER
