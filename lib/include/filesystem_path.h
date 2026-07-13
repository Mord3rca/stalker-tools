#ifndef STCORE_FILESYSTEM_PATH_HEADER
#define STCORE_FILESYSTEM_PATH_HEADER

#include <limits.h>

typedef struct {
	unsigned short len;
	unsigned short scount;
	unsigned short last_sep_offset;

	char target[PATH_MAX];
} stcore_filesystem_path;

stcore_filesystem_path *stcore_filesystem_path_create(const char[]);
int stcore_filesystem_path_init(stcore_filesystem_path *, const char[]);

int stcore_filesystem_path_copy(const stcore_filesystem_path, stcore_filesystem_path*);

int stcore_filesystem_path_cmp(const stcore_filesystem_path, const stcore_filesystem_path);
#define stcore_filesystem_path_equal(a, b)    (stcore_filesystem_path_cmp(a, b) == 0)
#define stcore_filesystem_path_is_absolute(p) (p.len > 0 && p.target[0] == '/')

int stcore_filesystem_path_dirname(const stcore_filesystem_path, stcore_filesystem_path*);
int stcore_filesystem_path_basename(const stcore_filesystem_path, stcore_filesystem_path*);

int stcore_filesystem_path_append(const stcore_filesystem_path, stcore_filesystem_path*);
int stcore_filesystem_path_prepend(const stcore_filesystem_path, stcore_filesystem_path*);

#endif //STCORE_FILESYSTEM_PATH_HEADER
