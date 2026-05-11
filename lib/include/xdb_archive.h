#ifndef _HEADER_ARCHIVE_XDB
#define _HEADER_ARCHIVE_XDB

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "dltx.h"
#include "dynarray.h"

#define XDB_DATA_CHUNK		0x00000000
#define XDB_METADATA		0x00000001
#define XDB_HEADER		0x0000029a
#define XDB_COMPRESS_FLAG	0x80000000

/*
 *  XDB CHUNK DEFINITIONS
 */

typedef struct {
	uint32_t type;
	uint32_t size;

	long fpos;		// position of header start in the file (without type/size)
} xdb_chunk;

bool xdb_chunk_is_compressed(const xdb_chunk);

/*
 * XDB METADATA
 */

typedef struct {
	uint32_t real_size;
	uint32_t comp_size;

	uint32_t crc;

	char *path;

	uint32_t ptr;
} xdb_metadata_entry;

void free_xdb_metadata_entry(xdb_metadata_entry*);

/*
 *  XDB DEFINITIONS
 */

#define XDB_MAX_CHUNKS	4  // Looks like most DB have only 3 chunks .. Lets put 4 just in case.

typedef struct {
	FILE *_f;

	xdb_chunk chunks[XDB_MAX_CHUNKS];
	char path[PATH_MAX];
} xdb;

xdb *xdb_archive_open(const char[PATH_MAX]);	// API may change (R/W flags, keep loaded, ...)
void xdb_archive_close(xdb*);

const xdb_chunk *xdb_get_chunk(const xdb*, unsigned long);
unsigned char *xdb_get_chunk_data(const xdb*, const xdb_chunk*, size_t*);

DLTX *xdb_get_header(const xdb*);

struct dynarray* xdb_read_metadata(const xdb*);
void free_xdb_metadata(struct dynarray*);

int xdb_extract_all(xdb*, const char[]);

#endif  // _HEADER_ARCHIVE_XDB
