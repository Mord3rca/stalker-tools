#ifndef _FILESSYTEM_HEADER
#define _FILESSYTEM_HEADER

#include "dynarray.h"

typedef enum {
	FS_NO_ERROR = 0,
	FS_GLOB_ERROR,
	FS_GLOB_NO_MATCH,

	FS_GENERIC_ERROR,
} fs_return_code;

int  filesystem_init(const char fsgame[]);
void filesystem_cleanup(void);

char *filesystem_path_append(const char p1[], const char p2[]);
char *filesystem_path_append2(const char path[], const char file[]);

fs_return_code filesystem_glob(const char path[], const char relative[], char **out[]);
char *filesystem_get_modfile_glob_path(const char path[]);
void filesystem_path_tolower(char path[]);

void filesystem_to_system_path(char path[]);

char *filesystem_canonicalize_path(const char path[]);
char *filesystem_canonicalize_directory(const char dir[]);

int filesystem_create_directory(const char dir[]);
int filesystem_create_subdir(const char file[]);

char *filesystem_resolve_path(const char path[]);

struct dynarray *filesystem_list_files(const char path[], int mdepth);

#endif  // _FILESSYTEM_HEADER
