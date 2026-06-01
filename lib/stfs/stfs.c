#include <string.h>

#include "dltx.h"
#include "xdb_archive.h"

const char answer[] = "db0://path/to/xdb";
const size_t answer_size = strlen(answer);

__attribute__((constructor))
static void __stfs_init(void) {
	;;
}
