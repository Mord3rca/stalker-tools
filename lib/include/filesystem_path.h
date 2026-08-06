#ifndef STCORE_FILESYSTEM_PATH_HEADER
#define STCORE_FILESYSTEM_PATH_HEADER

#include <limits.h>

typedef struct {
	unsigned short len;
	unsigned short scount;
	unsigned short last_sep_offset;

	char target[PATH_MAX];
} stcore_filesystem_path;

stcore_filesystem_path *stcore_filesystem_path_create(const char path[]);
int stcore_filesystem_path_init(stcore_filesystem_path *p, const char name[]);

int stcore_filesystem_path_copy(const stcore_filesystem_path src, stcore_filesystem_path *dest);

int stcore_filesystem_path_cmp(const stcore_filesystem_path a, const stcore_filesystem_path b);
#define stcore_filesystem_path_equal(a, b)    (stcore_filesystem_path_cmp(a, b) == 0)
#define stcore_filesystem_path_is_absolute(p) (p.len > 0 && p.target[0] == '/')

int stcore_filesystem_path_dirname(const stcore_filesystem_path a, stcore_filesystem_path *dir);
int stcore_filesystem_path_basename(const stcore_filesystem_path p, stcore_filesystem_path *base);

int stcore_filesystem_path_append(const stcore_filesystem_path src, stcore_filesystem_path *dst);
int stcore_filesystem_path_prepend(const stcore_filesystem_path src, stcore_filesystem_path *dst);

#endif //STCORE_FILESYSTEM_PATH_HEADER
