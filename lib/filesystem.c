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

#include "dynarray.h"
#include "filesystem.h"

struct filesystem_path_key {
	char *key;
	char *value;

	size_t key_size;
	unsigned char flags;
};

typedef struct {
	struct filesystem_path_key **keys;
} _filesystem_internal;

static _filesystem_internal _fs;

static char _init_buffer[PATH_MAX + 1];
static size_t _approot_size;

static struct filesystem_path_key *_create_fs_key(const char name[], const char path[], unsigned char flags) {
	size_t path_size = 0;
	struct filesystem_path_key *r = malloc(sizeof(struct filesystem_path_key));

	if (path) {
		path_size = strlen(path);
		memcpy(_init_buffer + _approot_size, path, path_size);
	}
	*(_init_buffer + _approot_size + path_size) = 0;

	r->key = strdup(name);
	r->key_size = strlen(r->key);  // Will be used for quick matching
	r->value = strdup(_init_buffer);
	r->flags = flags;

	return r;
}

int filesystem_init(void) {
	// Create fsgame.ltx keys statically
	// TODO: Read fsgame.ltx if exist
	// (need to rework a bit DLTX since file define only orphan keys)
	size_t i;
	struct dynarray *dyn = dynarray_create(16);

	getcwd(_init_buffer, PATH_MAX);  // No trailing /
	_approot_size = strlen(_init_buffer);
	_init_buffer[_approot_size++] = '/';

	// See <path/to/Anomaly>/fsgame.ltx for more info
	dynarray_insert(dyn, _create_fs_key("$fs_root$", NULL, 0));
	dynarray_insert(dyn, _create_fs_key("$app_data_root$", "appdata/", 0));
	dynarray_insert(dyn, _create_fs_key("$arch_dir$", "db/", 0));
	dynarray_insert(dyn, _create_fs_key("$arch_dir_configs$", "db/configs/", 0));
	dynarray_insert(dyn, _create_fs_key("$arch_dir_maps$", "db/levels/", 0));
	dynarray_insert(dyn, _create_fs_key("$game_data$", "gamedata/", 0));
	// TODO: Complete this for now, $fs_root$ & $gamedata$ is enough

	// Copy allocated struct to keys
	_fs.keys = calloc(sizeof(struct filesystem_path_key*), dyn->size + 1);
	for (i=0; i < dyn->size; i++)
		_fs.keys[i] = dyn->arr[i];
	_fs.keys[i++] = NULL;

	free_dynarray(dyn, NULL);

	return 0;
}

__attribute__((destructor))
void filesystem_cleanup(void) {
	size_t i;

	if (!_fs.keys) return;

	for (i=0; _fs.keys[i]; i++) {
		free(_fs.keys[i]->key);
		free(_fs.keys[i]->value);
	}
	free(_fs.keys);
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

	free(itstart);
	return r;
}

static const char *_filesystem_get_value(const char *start, const char *end) {
	size_t len = end - start + 1;
	struct filesystem_path_key **k;

	for (k=_fs.keys; *k; k++) {
		if (len != (*k)->key_size)
			continue;

		if (strncmp(start, (*k)->key, len) != 0)
			continue;

		break;
	}
	return *k ? (*k)->value : ".";
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
