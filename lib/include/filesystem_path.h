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

int stcore_filesystem_path_copy(stcore_filesystem_path *dest, const stcore_filesystem_path src);

int stcore_filesystem_path_cmp(const stcore_filesystem_path a, const stcore_filesystem_path b);
#define stcore_filesystem_path_equal(a, b)    (stcore_filesystem_path_cmp(a, b) == 0)
#define stcore_filesystem_path_is_absolute(p) (p.len > 0 && p.target[0] == '/')

int stcore_filesystem_path_dirname(stcore_filesystem_path *dir);
int stcore_filesystem_path_basename(stcore_filesystem_path *base);

int stcore_filesystem_path_append(stcore_filesystem_path *dst, const stcore_filesystem_path src);
// TODO: Still a bad name...
int stcore_filesystem_path_append2(stcore_filesystem_path *dst, const char path[], const char file[]);

int stcore_filesystem_path_prepend(stcore_filesystem_path *dst, const stcore_filesystem_path src);

int stcore_filesystem_path_append_str(stcore_filesystem_path *dst, const char src[]);
int stcore_filesystem_path_prepend_str(stcore_filesystem_path *dst, const char src[]);

void stcore_filesystem_path_to_system(stcore_filesystem_path *p);
void stcore_filesystem_path_to_lower(stcore_filesystem_path *p);

stcore_filesystem_path *stcore_filesystem_path_create_to_system(const char path[]);

void stcore_filesystem_path_canonicalize(stcore_filesystem_path *path);
char *stcore_filesystem_path_canonicalize_str(const char path[]);

#endif //STCORE_FILESYSTEM_PATH_HEADER
