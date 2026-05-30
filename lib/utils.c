#include <ctype.h>
#include <stddef.h>
#include <string.h>

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
