#ifndef _FILESSYTEM_HEADER
#define _FILESSYTEM_HEADER

#include "dynarray.h"
#include "filesystem_path.h"

typedef enum {
	FS_NO_ERROR = 0,
	FS_GLOB_ERROR,
	FS_GLOB_NO_MATCH,

	FS_GENERIC_ERROR,
} fs_return_code;

int  filesystem_init(const char fsgame[]);
void filesystem_cleanup(void);

fs_return_code filesystem_glob(const char path[], const char relative[], char **paths[]);

int filesystem_create_directory(const char dir[]);
int filesystem_create_subdir(const char file[]);

char *filesystem_resolve_path(const char path[]);

struct dynarray *filesystem_list_files(const char path[], int mdepth);

#endif  // _FILESSYTEM_HEADER
