#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <glob.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dltx.h"
#include "filesystem.h"
#include "utils.h"

struct filesystem_path_key {
	char *key;
	char *value;

	size_t key_size;
	unsigned char flags;
};

typedef struct {
	struct dynarray *keys;
} _filesystem_internal;

static _filesystem_internal _fs;

static const struct filesystem_path_key *_filesystem_get_key(const char key[])
{
	size_t len = strlen(key);
	const struct filesystem_path_key *k = NULL;

	DYNARRAY_INLINE_FOREACH(_fs.keys, const struct filesystem_path_key) {
		if (len != (*it)->key_size)
			continue;

		if (strncmp(key, (*it)->key, len) != 0)
			continue;

		k = *it;
		break;
	}
	return k;
}

static struct filesystem_path_key *_create_fs_root(const char fsgame[])
{
	stcore_filesystem_path buff;
	struct filesystem_path_key *r = NULL;


	stcore_filesystem_path_init(&buff, fsgame);
	stcore_filesystem_path_dirname(&buff);
	stcore_filesystem_path_canonicalize(&buff);

	r = malloc(sizeof(struct filesystem_path_key));
	r->key = strdup("$fs_root$");
	r->key_size = strlen(r->key);
	r->value = *buff.target ? strdup(buff.target) : strdup(".");
	r->flags = 0;

	return r;
}

static struct filesystem_path_key *_create_fs_key(const char name[], const char root[], const char add[], unsigned char flags)
{
	stcore_filesystem_path buffer;
	struct filesystem_path_key *r = NULL;
	const struct filesystem_path_key *rkey = NULL;

	stcore_filesystem_path_init(&buffer, "");

	if (root) {
		rkey = _filesystem_get_key(root);
		if (!rkey)
			goto create_fs_end;

		stcore_filesystem_path_append_str(&buffer, rkey->value);
	}

	if (add)
		stcore_filesystem_path_append_str(&buffer, add);

	stcore_filesystem_path_to_system(&buffer);
	stcore_filesystem_path_canonicalize(&buffer);

	r = malloc(sizeof(struct filesystem_path_key));
	r->key = strdup(name);
	r->key_size = strlen(r->key);  // Will be used for quick matching
	r->value = strdup(buffer.target);
	r->flags = flags;

create_fs_end:
	return r;
}

static bool _section_iterator(const DLTXKey *key, void *__args)
{
	size_t ts;
	char *s, **t;
	unsigned char f = 0;

	if (_filesystem_get_key(key->name))
		return true;

	s = strdup(key->value);
	t = split(s, "|", &ts);

	if (ts < 4)
		goto it_cleanup;

	if (parse_bool(t[0]))
		f |= 0x01; // recurs
	if (parse_bool(t[1]))
		f |= 0x02; // notif

	dynarray_insert(_fs.keys, _create_fs_key(key->name, t[2], t[3], f));

it_cleanup:
	free(t);
	free(s);
	return true;
}

int filesystem_init(const char fsgame[])
{
	DLTX *dltx;
	DLTXSection *sec;
	DLTX_RETURN_CODE dltx_err;

	dltx = dltx_create_from_file(fsgame, &dltx_err);
	if (!dltx)
		return 1;

	sec = dltx_find_section(dltx, "__default__");

	// +1 for $fs_root$
	_fs.keys = dynarray_create(sec->keys->size + 1);

	// See <path/to/Anomaly>/fsgame.ltx for more info
	dynarray_insert(_fs.keys, _create_fs_root(fsgame)); // Special case
	dynarray_insert(_fs.keys, _create_fs_key("$game_data$", "$fs_root$", "gamedata/", 3));

	if (sec)
		dynarray_foreach(sec->keys, (dynarray_cb)&_section_iterator, NULL);

	free_dltx(dltx);
	return 0;
}

static void _fs_free_key(struct filesystem_path_key *k)
{
	free(k->key);
	free(k->value);
	free(k);
}

__attribute__((destructor))
void filesystem_cleanup(void)
{
	free_dynarray(_fs.keys, (dynarray_free_cb)&_fs_free_key);
}

fs_return_code filesystem_glob(const char path[], const char relative[], char **out[])
{
	int err;
	char *tmp;
	glob_t gl;
	size_t offset = 0;
	char **result = NULL;

	if (relative) {
		tmp = strdup(relative);
		dirname(tmp);
		offset = strlen(tmp) + 1;
		free(tmp);
	}

	err = glob(path, 0, NULL, &gl);
	if (err != 0) {
		//free
		return err == GLOB_NOMATCH ? FS_GLOB_NO_MATCH : FS_GLOB_ERROR;
	}

	result = calloc(gl.gl_pathc + 1, sizeof(char *));
	result[gl.gl_pathc] = NULL;

	for (size_t j = 0; j < gl.gl_pathc; j++)
		result[j] = strdup(gl.gl_pathv[j] + offset);

	*out = result;

	globfree(&gl);
	return FS_NO_ERROR;
}

static char *filesystem_canonicalize_directory(const char dir[])
{
	char *cdir = NULL;
	size_t sdir = strlen(dir);

	if (sdir > PATH_MAX)
		return NULL;

	// Nothing to do
	if (*(dir + sdir - 1) == '/')
		return strdup(dir);

	cdir = malloc(PATH_MAX + 1);
	memcpy(cdir, dir, sdir);
	cdir[sdir++] = '/';
	cdir[sdir++] = 0;

	return cdir;
}

int filesystem_create_directory(const char dir[])
{
	int r;
	char *it, *itstart, *itend;

	itstart = it = filesystem_canonicalize_directory(dir);
	itend = itstart + strlen(itstart);

	while (it < itend) {
		if (*it != '/') {
			it++;
			continue;
		}

		*it = 0;
		r = mkdir(itstart, 0744);
		r = (errno == EEXIST ? 0 : r);
		*it = '/';

		if (r != 0)
			break;

		it++;
	}

	free(itstart);
	return r;
}

int filesystem_create_subdir(const char file[])
{
	char pdir[PATH_MAX + 1] = {0};
	size_t sfile = strlen(file);

	if (sfile > PATH_MAX)
		return -1;

	memcpy(pdir, file, sfile);
	dirname(pdir);

	return filesystem_create_directory(pdir);
}

static const char *_filesystem_get_value(const char *start, const char *end)
{
	char key[256] = {0};
	const struct filesystem_path_key *k;

	if ((end - start) > 256)
		return NULL;

	memcpy(key, start, end - start + 1);

	k = _filesystem_get_key(key);
	return k ? k->value : ".";
}

char *filesystem_resolve_path(const char path[])
{
	char *wcur;
	const char *cur, *cur2;
	char wbuff[PATH_MAX] = {0};

	if (!_fs.keys)
		return NULL;

	for (cur = path, wcur = wbuff; *cur; cur++) {
		if (*cur != '$') {
			*(++wcur) = *cur;
			continue;
		}
		// Probably a var.
		cur2 = cur;
		for (cur = cur + 1; *cur; cur++) {
			if (*cur == '$')
				break; // TODO: Need something if it fails
		}
		wcur = stpcpy(wcur, _filesystem_get_value(cur2, cur)) - 1;
	}

	return strdup(wbuff);
}

static int _fs_filter_dot_dir(const struct dirent *d)
{
	if (!(d->d_type & DT_DIR))
		return 1;

	return strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0;
}

static int _fs_read_directory_content(struct dynarray *dyn, const char path[], int depth, int mdepth)
{
	int l, r = 0;
	stcore_filesystem_path npath;
	struct dirent **files, **it, **itend;

	if (mdepth != -1 && depth >= mdepth)
		return 0;

	l = scandir(path, &files, &_fs_filter_dot_dir, NULL);
	if (l < 0) {
		fprintf(stderr, "scandir() failed: %m\n");
		return 1;
	}

	for (it = files, itend = files + l; it < itend; it++) {
		stcore_filesystem_path_init(&npath, path);
		stcore_filesystem_path_append_str(&npath, (*it)->d_name);
		stcore_filesystem_path_canonicalize(&npath);

		if ((*it)->d_type != DT_DIR) {
			dynarray_insert(dyn, strdup(npath.target));
			continue;
		}

		r = _fs_read_directory_content(dyn, npath.target, depth + 1, mdepth);

		if (r != 0)
			break;

		continue;
	}

	free(files);
	return r;
}

struct dynarray *filesystem_list_files(const char path[], int mdepth)
{
	struct dynarray *dyn = dynarray_create(24);

	if (_fs_read_directory_content(dyn, path, 0, mdepth) != 0) {
		free_dynarray(dyn, (dynarray_free_cb)&free);
		return NULL;
	}

	return dyn;
}
