#include <ctype.h>
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
#include "dynarray.h"
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

static const struct filesystem_path_key *_filesystem_get_key(const char key[]) {
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

static struct filesystem_path_key *_create_fs_root(const char fsgame[]) {
	char buffer[PATH_MAX + 1] = {0};
	struct filesystem_path_key *r = NULL;

	strncpy(buffer, fsgame, PATH_MAX);
	dirname(buffer);
	strcat(buffer, "/");

	r = malloc(sizeof(struct filesystem_path_key));
	r->key = strdup("$fs_root$");
	r->key_size = strlen(r->key);
	r->value = strdup(buffer);
	r->flags = 0;

	return r;
}

static struct filesystem_path_key *_create_fs_key(const char name[], const char root[], const char add[], unsigned char flags) {
	char buffer[PATH_MAX + 1] = {0};
	struct filesystem_path_key *r = NULL;
	const struct filesystem_path_key *rkey = NULL;

	if (root) {
		rkey = _filesystem_get_key(root);
		if (!rkey)
			goto create_fs_end;

		strcat(buffer, rkey->value);
	}

	if (add) {
		if (*buffer && buffer[strlen(buffer) -1] != '/')
			strcat(buffer, "/");

		strcat(buffer, add);
	}

	filesystem_to_system_path(buffer);

	r = malloc(sizeof(struct filesystem_path_key));
	r->key = strdup(name);
	r->key_size = strlen(r->key);  // Will be used for quick matching
	r->value = strdup(buffer);
	r->flags = flags;

create_fs_end:
	return r;
}

static bool _section_iterator(const DLTXKey *key, void *__args) {
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

int filesystem_init(const char fsgame[]) {
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
	//dynarray_insert(_fs.keys, _create_fs_key("$fs_root$", NULL, NULL, 0)); // Special case
	dynarray_insert(_fs.keys, _create_fs_root(fsgame)); // Special case
	dynarray_insert(_fs.keys, _create_fs_key("$game_data$", "$fs_root$", "gamedata/", 3));

	if (sec)
		dynarray_foreach(sec->keys, (dynarray_cb)&_section_iterator, NULL);

	free_dltx(dltx);
	return 0;
}

static void _fs_free_key(struct filesystem_path_key *k) {
	free(k->key);
	free(k->value);
	free(k);
}

__attribute__((destructor))
void filesystem_cleanup(void) {
	free_dynarray(_fs.keys, (dynarray_free_cb)&_fs_free_key);
}

void filesystem_to_system_path(char path[]) {
	char *cur = path;

	if (!cur)
		return;

	while(*cur != 0) {
		if (*cur == '\\')
			*cur = '/';
		cur++;
	}
}

void filesystem_path_tolower(char path[]) {
	char *cur = path;

	if ( !cur )
		return;

	while ( *cur != 0 ) {
		*cur = tolower(*cur);
		cur++;
	}
}

char *filesystem_path_append(const char *path, const char *file) {
	char r[PATH_MAX] = {0};
	char p[PATH_MAX] = {0};

	strcpy(p, path);
	strcpy(r, dirname(p));

	strcat(r, "/");
	strcat(r, file);

	filesystem_to_system_path(r);

	return strdup(r);
}


fs_return_code filesystem_glob(const char path[], const char relative[], char **out[]) {
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

	result = calloc(sizeof(char*), gl.gl_pathc + 1);
	result[gl.gl_pathc] = NULL;

	for (size_t j = 0; j < gl.gl_pathc; j++) {
		result[j] = strdup(gl.gl_pathv[j] + offset);
	}

	*out = result;

	globfree(&gl);
	return FS_NO_ERROR;
}

char *filesystem_get_modfile_glob_path(const char path[]) {
	char *buffer;
	char *filename, *temp;

	buffer = strdup(path);
	filename = basename(buffer);

	temp = strstr(filename, ".ltx");
	if (temp)
		*temp = 0;

	temp = calloc(sizeof(char), PATH_MAX);

	snprintf(temp, PATH_MAX, "mod_%s_*.ltx", filename);

	free(buffer);
	return temp;
}

int filesystem_create_directory(const char dir[]) {
	int r;
	char *it, *itstart, *itend;

	itstart = it = strdup(dir);
	itend = itstart + strlen(dir);

	while (it < itend) {
		if (*it != '/') {
			it++;
			continue;
		}

		*it = 0;
		r = mkdir(itstart, S_IRWXU);
		r = (errno == EEXIST ? 0 : r);
		*it = '/';

		if (r != 0)
			break;

		it++;
	}

	// In case end char is not / ... If it was, this does nothing
	r = mkdir(itstart, S_IRWXU);
	r = (errno == EEXIST ? 0 : r);

	free(itstart);
	return r;
}

int filesystem_create_subdir(const char path[]) {
	char pdir[PATH_MAX] = {0};

	memcpy(pdir, path, strlen(path));
	dirname(pdir);

	return filesystem_create_directory(pdir);
}

static const char *_filesystem_get_value(const char *start, const char *end) {
	char key[256] = {0};
	const struct filesystem_path_key *k;

	if ((end - start) > 256)
		return NULL;

	memcpy(key, start, end - start + 1);

	k = _filesystem_get_key(key);
	return k ? k->value : ".";
}

char *filesystem_resolve_path(const char path[]) {
	char *wcur;
	const char *cur, *cur2;
	char wbuff[PATH_MAX] = {0};

	if(!_fs.keys) return NULL;

	for (cur=path, wcur=wbuff; *cur; cur++) {
		if (*cur != '$') {
			*(++wcur) = *cur;
			continue;
		}
		// Probably a var.
		cur2 = cur;
		for (cur=cur+1; *cur; cur++) {
			if (*cur == '$')
				break; // TODO: Need something if it fails
		}
		wcur = stpcpy(wcur, _filesystem_get_value(cur2, cur)) - 1;
	}

	return strdup(wbuff);
}
