#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "filesystem_path.h"
#include "utils.h"

int stcore_filesystem_path_init(stcore_filesystem_path *p, const char name[])
{
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

stcore_filesystem_path *stcore_filesystem_path_create(const char path[])
{
	stcore_filesystem_path *p = malloc(sizeof(stcore_filesystem_path));

	stcore_filesystem_path_init(p, path);

	return p;
}

int stcore_filesystem_path_copy(stcore_filesystem_path *dest, const stcore_filesystem_path src)
{
	if (!dest)
		return -1;

	memcpy(dest, &src, sizeof(stcore_filesystem_path));
	return 0;
}

int stcore_filesystem_path_cmp(const stcore_filesystem_path a, const stcore_filesystem_path b)
{
	return a.scount != b.scount ?
	    (a.scount > b.scount ? 1 : -1) :
	    strcasecmp(a.target, b.target);
}

int stcore_filesystem_path_dirname(stcore_filesystem_path *dir)
{
	if (!dir)
		return -1;

	if (stcore_filesystem_path_is_absolute((*dir)) && dir->last_sep_offset == 0) {
		stcore_filesystem_path_init(dir, "/");
		return 0;
	}

	if (dir->scount == 0) {
		stcore_filesystem_path_init(dir, ".");
		return 0;
	}

	dir->len = dir->last_sep_offset;
	dir->target[dir->len] = 0;
	dir->scount--;
	dir->last_sep_offset = 0;

	for (unsigned short i = dir->len - 1;; i--) {
		if (dir->target[i] == '/') {
			dir->last_sep_offset = i;
			break;
		}

		if (i == 0)
			break;
	}

	return 0;
}

int stcore_filesystem_path_basename(stcore_filesystem_path *base)
{
	size_t oset_off = base->last_sep_offset;

	if (!base)
		return -1;

	// No separator, already a basename
	if (base->scount == 0)
		return 0;

	base->len -= base->last_sep_offset + 1;
	base->scount = 0;
	base->last_sep_offset = 0;

	// Avoid valgrind overlap defect
	//strncpy(base->target, base->target + oset_off + 1, base->len);
	for (unsigned short i = 0; i < base->len; i++)
		base->target[i] = base->target[i + oset_off + 1];

	base->target[base->len] = 0;

	return 0;
}

int stcore_filesystem_path_append(stcore_filesystem_path *dst, const stcore_filesystem_path src)
{
	if (!dst)
		return -1;

	if ((src.len + dst->len) > PATH_MAX)
		return -1;

	if (dst->len != 0 && dst->target[dst->len] != '/' && src.target[0] != '/') {
		dst->scount++;
		dst->target[dst->len++] = '/';
	}
	strncpy(dst->target + dst->len, src.target, src.len);

	dst->scount += src.scount;
	if (src.scount > 0)
		dst->last_sep_offset = dst->len + src.last_sep_offset;
	dst->len += src.len;
	dst->target[dst->len] = 0;

	return 0;
}

int stcore_filesystem_path_append2(stcore_filesystem_path *dst, const char path[], const char file[])
{
	stcore_filesystem_path p;

	stcore_filesystem_path_init(&p, path);
	stcore_filesystem_path_dirname(&p);
	stcore_filesystem_path_append_str(&p, file);

	stcore_filesystem_path_to_system(&p);

	stcore_filesystem_path_copy(dst, p);

	return 0;
}

int stcore_filesystem_path_prepend(stcore_filesystem_path *dst, const stcore_filesystem_path src)
{
	size_t off = 0;
	char buf[PATH_MAX] = {0};

	if (!dst)
		return -1;

	if ((src.len + dst->len) > PATH_MAX)
		return -1;

	if (src.len == 0)
		return 0;

	strncpy(buf, src.target, src.len);
	if (src.target[src.len - 1] != '/' && dst->target[0] != '/') {
		buf[src.len] = '/';
		off++;
	}
	strncpy(buf + src.len + off, dst->target, dst->len);

	stcore_filesystem_path_init(dst, buf);

	return 0;
}

int stcore_filesystem_path_append_str(stcore_filesystem_path *dst, const char src[])
{
	stcore_filesystem_path t;

	stcore_filesystem_path_init(&t, src);
	return stcore_filesystem_path_append(dst, t);
}

int stcore_filesystem_path_prepend_str(stcore_filesystem_path *dst, const char src[])
{
	stcore_filesystem_path t;

	stcore_filesystem_path_init(&t, src);
	return stcore_filesystem_path_prepend(dst, t);
}

void stcore_filesystem_path_to_system(stcore_filesystem_path *p)
{
	char *c;

	if (!p)
		return;

	p->scount = 0;
	for (c = p->target; *c; c++) {
		switch (*c) {
		case '\\':
			*c = '/';
		case '/':
			p->scount++;
			p->last_sep_offset = c - p->target;
			break;
		default:
		}
	}
}

void stcore_filesystem_path_to_lower(stcore_filesystem_path *p)
{
	char *c;

	if (!p)
		return;

	for (c = p->target; *c; c++)
		*c = tolower(*c);
}

stcore_filesystem_path *stcore_filesystem_path_create_to_system(const char path[])
{
	stcore_filesystem_path *p;

	p = stcore_filesystem_path_create(path);
	stcore_filesystem_path_to_system(p);

	return p;
}

void stcore_filesystem_path_canonicalize(stcore_filesystem_path *path)
{
	size_t sep_len;
	char *wcur, **sep, **scur;
	char buffer[PATH_MAX] = {0};
	stcore_filesystem_path tmp = {0};  // Will use buffer & counters

	strncpy(buffer, path->target, path->len);
	sep = split(buffer, "/", &sep_len);
	if (!sep)
		return;

	scur = sep;
	wcur = tmp.target;
	tmp.scount = sep_len - 1;

	if (stcore_filesystem_path_is_absolute((*path))) {
		wcur = stpcpy(wcur, "/");
		tmp.scount++;
	}

	for (; *scur; scur++) {
		// Ignore . dir
		if (strcmp(*scur, ".") == 0) {
			tmp.scount--;
			continue;
		}

		tmp.last_sep_offset = wcur - tmp.target;
		wcur = stpcpy(wcur, *scur);
		wcur = stpcpy(wcur, "/");
	}

	tmp.len = wcur - tmp.target;
	if (tmp.len > 0)
		tmp.target[--tmp.len] = 0;  // Del trailing /

	stcore_filesystem_path_copy(path, tmp);

	free(sep);
}

char *stcore_filesystem_path_canonicalize_str(const char path[])
{
	stcore_filesystem_path p;

	stcore_filesystem_path_init(&p, path);
	stcore_filesystem_path_canonicalize(&p);

	return strdup(p.target);
}
