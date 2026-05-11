#include <ctype.h>
#include <errno.h>
#include <glob.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "filesystem.h"

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
	char *r = calloc(sizeof(char), PATH_MAX);
	char p[PATH_MAX] = {0};

	strcpy(p, path);
	memset(r, 0, PATH_MAX);
	strcpy(r, dirname(p));

	strcat(r, "/");
	strcat(r, file);

	filesystem_to_system_path(r);

	return r;
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
