#include <ctype.h>
#include <stddef.h>
#include <string.h>

#include "dynarray.h"

static char* _rstrip(char *s) {
	char *cur, *end;
	size_t l = strlen(s);

	for(cur = s, end = s + l; cur < end && isspace(*cur); *(cur++) = 0);

	return cur != end ? cur : NULL;
}

static char *_lstrip(char *s) {
	char *cur, *end;
	size_t l = strlen(s) - 1;

	for(cur = s + l, end = s; cur > end && isspace(*cur); *(cur--) = 0);

	return cur != end ? s : NULL;
}

char *strip(char *s) {
	s = _rstrip(s);
	if (s)
		_lstrip(s);

	return s;
}

char **split(char *str, const char *delims, size_t *size) {
	char *s, *t;
	char **result;
	struct dynarray *dyn = dynarray_create(16);

	s = strtok(str, delims);
	dynarray_insert(dyn, s);
	while (s != NULL) {
		s = strtok(NULL, delims);
		t = s ? strip(s) : NULL;
		dynarray_insert(dyn, t);
	}

	result = (char**)dyn->arr;
	dyn->arr = NULL;
	if (size)
		*size = dyn->size - 1;

	free_dynarray(dyn, NULL);
	return result;
}
