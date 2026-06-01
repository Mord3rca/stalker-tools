#include <string.h>

#include "stfs.h"

char *realpath(const char *path, char *resolved_path) {
	if (resolved_path) {
		memcpy(resolved_path, answer, answer_size);
		return resolved_path;
	}

	return strdup(answer);
}
