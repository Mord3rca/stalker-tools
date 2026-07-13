#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "filesystem_path.h"

int stcore_filesystem_path_init(stcore_filesystem_path *p, const char name[]) {
	size_t i;

	p->len = 0;
	p->scount = 0;
	p->last_sep_offset = 0;

	for (i = 0; name[i]; i++) {
		if (name[i] == '/') {
			p->scount++;
			p->last_sep_offset = i;
		}
		p->target[i] = name[i];
	}
	p->len = i;
	p->target[i++] = 0;

	return 0;
}

stcore_filesystem_path *stcore_filesystem_path_create(const char path[]) {
	stcore_filesystem_path *p = malloc(sizeof(stcore_filesystem_path));

	stcore_filesystem_path_init(p, path);

	return p;
}

int stcore_filesystem_path_copy(const stcore_filesystem_path src, stcore_filesystem_path *dest) {
	if (!dest)
		return -1;

	memcpy(dest, &src, sizeof(stcore_filesystem_path));
	return 0;
}

int stcore_filesystem_path_cmp(const stcore_filesystem_path a, const stcore_filesystem_path b) {
	return a.scount != b.scount ?
	    (a.scount > b.scount ? 1 : -1) :
	    strcasecmp(a.target, b.target);
}

int stcore_filesystem_path_dirname(const stcore_filesystem_path a, stcore_filesystem_path *dir) {
	if (!dir)
		return -1;

	if (stcore_filesystem_path_is_absolute(a) && a.last_sep_offset == 0) {
		stcore_filesystem_path_init(dir, "/");
		return 0;
	}

	dir->len = a.last_sep_offset;
	dir->scount = a.scount - 1;
	dir->last_sep_offset = 0;

	strncpy(dir->target, a.target, dir->len);
	dir->target[dir->len] = 0;

	for(unsigned short i = 0; dir->target[i]; i++)
		if (dir->target[i] == '/')
			dir->last_sep_offset = i;

	return 0;
}

int stcore_filesystem_path_basename(const stcore_filesystem_path p, stcore_filesystem_path *base) {
	if (!base)
		return -1;

	base->len = p.len - p.last_sep_offset + 1;
	base->scount = 0;
	base->last_sep_offset = 0;

	strncpy(base->target, p.target + p.last_sep_offset + 1, base->len);

	return 0;
}

int stcore_filesystem_path_append(const stcore_filesystem_path src, stcore_filesystem_path *dst) {
	if (!dst)
		return -1;

	if ((src.len + dst->len) > PATH_MAX)
		return -1;

	strncpy(dst->target + dst->len, src.target, src.len);

	dst->scount += src.scount;
	if (src.scount > 0)
		dst->last_sep_offset = dst->len + src.last_sep_offset;
	dst->len += src.len;

	return 0;
}

int stcore_filesystem_path_prepend(const stcore_filesystem_path src, stcore_filesystem_path *dst) {
	char buf[PATH_MAX] = {0};

	if (!dst)
		return -1;

	if ((src.len + dst->len) > PATH_MAX)
		return -1;

	strncpy(buf, src.target, src.len);
	strncpy(buf + src.len, dst->target, dst->len);

	stcore_filesystem_path_init(dst, buf);

	return 0;
}
