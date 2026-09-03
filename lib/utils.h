#ifndef _HEADER_UTILS
#define _HEADER_UTILS

#include <stdbool.h>

char *strip(char *s);
char **split(char *str, const char *delims, size_t *size);
bool parse_bool(const char *str);

#endif //_HEADER_UTILS
