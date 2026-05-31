#include <lzo1x.h>
#include <stdlib.h>
#include <string.h>

#include "xdb_archive.h"
#include "filesystem.h"
#include "huffman.h"

// XDB CHUNK

bool xdb_chunk_is_compressed(const xdb_chunk a) {
	return a.type & XDB_COMPRESS_FLAG;
}

// XDB METADATA ENTRY

void free_xdb_metadata_entry(xdb_metadata_entry *e) {
	free(e->path);
	free(e);
}

// XDB ARCHIVE

static int _xdb_read_chunk(xdb *archive) {
	size_t l;
	long flen;
	xdb_chunk *b;
	union {
		xdb_chunk a;
		unsigned char buff[8];
	} u;
	FILE *f = archive->_f;

	fseek(f, 0, SEEK_END);
	flen = ftell(f);

	fseek(f, 0, SEEK_SET);
	for(l = 0; l < XDB_MAX_CHUNKS; l++) {
		b = archive->chunks + l;

		if(fread(u.buff, 1, 8, f) != 8)
			return 1;

		b->type = u.a.type;
		b->size = u.a.size;
		b->fpos = ftell(f);

		if (fseek(f, u.a.size, SEEK_CUR) == -1)
			return 1;

		if (ftell(f) == flen)
			break;  // EOF
	}
	return 0;
}

xdb *xdb_archive_open(const char path[PATH_MAX]) {
	xdb *archive = malloc(sizeof(xdb));
	memset(archive, 0, sizeof(xdb));

	archive->_f = fopen(path, "r");
	if (!archive->_f) {
		free(archive);
		return NULL;
	}

	strncpy(archive->path, path, PATH_MAX);
	if (_xdb_read_chunk(archive) < 0) {
		xdb_archive_close(archive);
		return NULL;
	}

	return archive;
}

void xdb_archive_close(xdb *archive) {
	if (archive->_f)
		fclose(archive->_f);

	free(archive);
}

const xdb_chunk *xdb_get_chunk(const xdb *x, unsigned long type) {
	size_t i;
	for (i = 0; i < XDB_MAX_CHUNKS; i++) {
		if ((x->chunks[i].type & ~XDB_COMPRESS_FLAG) == type)
			return x->chunks + i;
	}
	return NULL;
}

unsigned char *xdb_get_chunk_data(const xdb *x, const xdb_chunk *c, size_t *size) {
	FILE *f = x->_f;
	size_t decomp_size = -1;
	unsigned char *decomp, *data;

	data = malloc(c->size + 1);

	fseek(f, c->fpos, SEEK_SET);
	fread(data, 1, c->size, f);

	if (xdb_chunk_is_compressed(*c)) {
		huffman_decompress((void**)&decomp, size ? size : &decomp_size, data, c->size);
		free(data);
		return decomp;
	}

	*size = decomp_size == -1 ? c->size : decomp_size;

	return data;
}

DLTX *xdb_get_header(const xdb *x) {
	DLTX *d;
	size_t data_s;
	const xdb_chunk *c;
	unsigned char *data;

	c = xdb_get_chunk(x, XDB_HEADER);
	if (!c)
		return NULL;

	d = dltx_create();
	data = xdb_get_chunk_data(x, c, &data_s);
	if (!data) {
		free_dltx(d);
		return NULL;
	}

	if (dltx_read_buffer(d, (char*)data, data_s) != NO_ERROR) {
		free(data);
		free_dltx(d);
		return NULL;
	}

	free(data);
	return d;
}

static unsigned short _read_ushort(unsigned char **cur) {
	unsigned short *r = (unsigned short*)(*cur);
	*cur += sizeof(unsigned short);
	return *r;
}

static uint32_t _read_uint32(unsigned char **cur) {
	uint32_t *r = (uint32_t*)(*cur);
	*cur += sizeof(uint32_t);
	return *r;
}

static char *_read_string(unsigned char **cur, size_t s) {
	char t, *e, *r;

	e = (char*)(*cur + s);
	t = *e;
	*e = 0;
	r = strdup((char*)*cur);
	*e = t;

	*cur += s;
	return r;
}

struct dynarray *xdb_read_metadata(const xdb *x) {
	size_t dsize, tmp;
	const xdb_chunk *c;
	struct dynarray *r;
	unsigned short esize;
	unsigned char *dstart, *dend, *dcur;
	xdb_metadata_entry *entry;

	c = xdb_get_chunk(x, XDB_METADATA);
	if (!c) {
		return NULL;
	}

	r = dynarray_create(32);

	dstart = xdb_get_chunk_data(x, c, &dsize);
	dend = dstart + dsize;

	dcur = dstart;
	while(dcur < dend) {
		esize = _read_ushort(&dcur);

		if (esize < (sizeof(uint32_t) * 4))
			break;

		entry = malloc(sizeof(xdb_metadata_entry));

		entry->real_size = _read_uint32(&dcur);
		entry->comp_size = _read_uint32(&dcur);
		entry->crc       = _read_uint32(&dcur);

		tmp = esize - sizeof(uint32_t)*4;
		entry->path = _read_string(&dcur, tmp);
		filesystem_to_system_path(entry->path);

		entry->ptr = _read_uint32(&dcur);

		dynarray_insert(r, entry);
	}

	free(dstart);
	return r;
}

void free_xdb_metadata(struct dynarray *entries) {
	free_dynarray(entries, (dynarray_free_cb)&free_xdb_metadata_entry);
}

typedef struct {
	int r;
	size_t data_size;
	unsigned char *data;
	const char *target;

	long foffset;
} extract_all_args;

static void _free_attrib(char **p) {
	if (!p) return;
	free(*p);
}

static void _close_file(FILE **f) {
	if (!f || !(*f)) return;

	fclose(*f);
}

static bool _xdb_extract_iterator(xdb_metadata_entry *entry, extract_all_args *args) {
	size_t size, poffset = entry->ptr - args->foffset;
	FILE *out __attribute__((cleanup(_close_file))) = NULL;
	char *buffer __attribute__((cleanup(_free_attrib))) = NULL;

	if (entry->real_size == 0 && entry->ptr == 0) {
		args->r = filesystem_create_directory(entry->path);
		return args->r == 0;
	}

	if (poffset < 0) {
		// Should not be possible
		args->r = 1;
		return false;
	}

	if ((poffset + entry->comp_size) > args->data_size) {
		args->r = 1;
		return false;
	}

	size = entry->real_size;

	if (entry->real_size != entry->comp_size) {
		buffer = malloc(size);
		// TODO: Better workaround (after huffman rewrite ?)
		if (lzo1x_decompress((lzo_bytep)args->data + poffset, entry->comp_size, (lzo_bytep)buffer, &size, NULL) != 0 ) {
			args->r = 1;
			return false;
		}

		if (size != entry->real_size) {
			fprintf(stderr, "SIZE MISMATCH FOR %s\n", entry->path);
		}
	}

	// Check CRC

	// Make sure DIR exist
	filesystem_create_subdir(entry->path);

	out = fopen(entry->path, "w");
	if (!out) {
		args->r = 1;
		return false;
	}
	fwrite(buffer ? buffer : (char*)(args->data + poffset), size, 1, out);

	return args->r == 0;
}

int xdb_extract_all(xdb *archive, const char path[]) {
	extract_all_args args;
	const xdb_chunk *cdata;
	struct dynarray *metadata;

	metadata = xdb_read_metadata(archive);
	if (!metadata)
		return 1;

	cdata = xdb_get_chunk(archive, XDB_DATA_CHUNK);
	if (!cdata) {
		free_xdb_metadata(metadata);
		return 1;
	}

	args.data = xdb_get_chunk_data(archive, cdata, &args.data_size);
	if (!args.data) {
		free_xdb_metadata(metadata);
		return 1;
	}

	args.r = 0;
	args.target = path;
	args.foffset = cdata->fpos;
	dynarray_foreach(metadata, (dynarray_cb)&_xdb_extract_iterator, &args);

	free(args.data);
	free_xdb_metadata(metadata);
	return args.r;
}
