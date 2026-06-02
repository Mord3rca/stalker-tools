#define FUSE_USE_VERSION 31

#include <ctype.h>
#include <errno.h>
#include <fuse.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dltx.h"
#include "dynarray.h"
#include "filesystem.h"
#include "filesystem_path.h"
#include "xdb.h"

static struct options {
	const char *stpath;
	const char *stcache;
	int use_cache;
	int show_help;
} options;

#define STFS_OPT(t, m) {t, offsetof(struct options, m), 1}

static const struct fuse_opt option_spec[] = {
	STFS_OPT("--st_path=%s", stpath),
	STFS_OPT("--st_cache_path=%s", stcache),
	STFS_OPT("--st_use_cache", use_cache),
	STFS_OPT("-h", show_help),
	STFS_OPT("--help", show_help),
	FUSE_OPT_END
};

static void show_help(const char prgname[]) {
	printf(
	    "Usage: %s [options] <mountpoint>\n"
	    "STFS specific options:\n"
	    "    --stfs_path=<s>      	Path to the STALKER $fs_root$\n"
	    "    --stfs_cache_path=<s>	Path relative to stpath of the\n"
	    "                         	STFS INI cache file (to write and/or to use)\n"
	    "                         	(Default: .stfs_cache.ini)\n"
	    "    --stfs_use_cache     	Enable cache function\n"
	    "\n"
	, prgname ? prgname : "stenv");
}

// Only used during config creation/parsing
static DLTXSection *stfs_cfg;
static DLTXSection *stfs_map;
static DLTXSection *stfs_db_preload;

static const char sec_cfg_name[]     = "config";
static const char sec_map_name[]     = "mapping";
static const char sec_preload_name[] = "preload";

static const char stfs_default_cache_filename[] = ".stfs_cache.ini";

// STFS Item declarations

typedef enum {
	STFS_ITEM_DIR,
	STFS_ITEM_LINK,
	STFS_ITEM_DB_MEMBER,
} stfs_item_type;

typedef struct {
	stfs_item_type type;
	stcore_filesystem_path fs_path;

	union {
		char *link;
		struct dynarray *dir_list;
	} arg;
} stfs_item;

static struct dynarray *fs_dirs;
static struct dynarray *fs_items;

static stcore_filesystem_path root_path;

static void stfs_item_init(stfs_item *item, const char name[], const char value[]) {
	item->type = STFS_ITEM_LINK;

	stcore_filesystem_path_init(&(item->fs_path), name);
	stcore_filesystem_path_prepend(root_path, &(item->fs_path));

	for(char *i = item->fs_path.target; *i; i++)
		*i = tolower(*i);

	item->arg.link = value ? strdup(value) : NULL;
}

static stfs_item *stfs_item_create_dir(const stcore_filesystem_path p) {
	stfs_item *i = malloc(sizeof(stfs_item));

	i->type = STFS_ITEM_DIR;
	stcore_filesystem_path_copy(p, &(i->fs_path));
	i->arg.dir_list = dynarray_create(24);

	for(char *j = i->fs_path.target; *j; j++)
		*j = tolower(*j);

	dynarray_insert(fs_dirs, i);
	dynarray_insert(fs_items, i);

	return i;
}

static void stfs_item_free(stfs_item *i) {
	if (!i) return;

	switch (i->type) {
	case STFS_ITEM_DIR:
		free_dynarray(i->arg.dir_list, NULL);
		break;
	default:
		free(i->arg.link);
	}

	free(i);
}

static int stfs_item_sort(const stfs_item **a, const stfs_item **b) {
	return stcore_filesystem_path_cmp((*a)->fs_path, (*b)->fs_path);
}

static inline bool _non_ascii_path(const char path[]) {
	for(const char *c = path; *c; c++) {
		if (!isascii(*c))
			return true;
	}

	return false;
}

static void _register_db_elements(xdb *f, DLTX *header) {
	struct dynarray *metadata;
	char *tmp, *fpath, *cpath, *rpath, buffer[PATH_MAX * 2];

	metadata = xdb_read_metadata(f);
	if (!metadata)
		return;

	// TODO: Better FS lib for transparency resolve
	//rpath = filesystem_resolve_path(dltx_get_key(header, "header", "entry_point"));
	rpath = strdup("gamedata/"); // All of them are writting to gamedata/
	if (!rpath)
		return;

	fpath = filesystem_canonicalize_path(f->path);

	DYNARRAY_INLINE_FOREACH(metadata, const xdb_metadata_entry) {
		if (XDB_METADATA_ENTRY_IS_DIR((*it)))
			continue;

		// Filter out weird path
		if (_non_ascii_path((*it)->path)) {
			fprintf(stderr, "Ignoring %s because it is weird.\n", (*it)->path);
			continue;
		}

		tmp = filesystem_path_append(rpath, (*it)->path);
		cpath = filesystem_canonicalize_path(tmp);
		snprintf(buffer, PATH_MAX * 2, "xdb://%s:%s", fpath, (*it)->path);

		dltx_section_set_key(stfs_map, cpath, buffer);

		free(tmp);
		free(cpath);
	}

	free(rpath);
	free(fpath);
	free_xdb_metadata(metadata);
}

static int parse_db_overrides(void) {
	struct dynarray *dbs;
	xdb *file;
	const char *v;
	DLTX *header = NULL;
	char *t, *datapath = filesystem_resolve_path("$arch_dir$");

	dbs = filesystem_list_files(datapath, -1);
	DYNARRAY_INLINE_FOREACH(dbs, const char) {
		file = xdb_archive_open(*it);
		if (!file)
			continue;

		header = xdb_get_header(file);
		if (!header) {
			xdb_archive_close(file);
			continue;
		}

		v = dltx_get_key(header, "header", "auto_load");
		if (v && strcmp(v, "true") == 0) {
			t = filesystem_canonicalize_path(*it);
			dltx_section_set_key(stfs_db_preload, t, NULL);
			free(t);
			_register_db_elements(file, header);
		}

		free_dltx(header);
		xdb_archive_close(file);
	}

	free(datapath);
	free_dynarray(dbs, &free);
	return 0;
}

static int parse_cur_fs(void) {
	char *t;
	struct dynarray *files = filesystem_list_files(".", -1);

	if (!files)
		return 1;

	DYNARRAY_INLINE_FOREACH(files, const char) {
		t = filesystem_canonicalize_path(*it);
		dltx_section_set_key(stfs_map, t, NULL);
		free(t);
	}

	free_dynarray(files, &free);
	return 0;
}

static void write_to_file(DLTX *root, const char path[]) {
	FILE *f;

	f = fopen(path, "w");
	if (!f) return;

	dltx_save_to_file(root, f);

	fclose(f);
}

static int _bsearch_find_by_path(const stcore_filesystem_path *p, const stfs_item **i) {
	return stcore_filesystem_path_cmp(*p, (*i)->fs_path);
}

static const stfs_item *stfs_find_item_by_path(const char fpath[]) {
	stfs_item **i;
	stcore_filesystem_path p;

	stcore_filesystem_path_init(&p, fpath);

	i = bsearch(
	  &p, fs_items->arr, fs_items->size, sizeof(stfs_item*),
	  (int (*)(const void*, const void*))_bsearch_find_by_path
	);

	return (i ? *i : NULL);
}

static int stfs_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
	int res = 0;
	const stfs_item *it;

	it = stfs_find_item_by_path(path);
	if (!it)
		return -ENOENT;

	switch(it->type) {
	case STFS_ITEM_DIR:
		stbuf->st_mode = S_IFDIR | 0555;
		stbuf->st_nlink = 2;
		break;
	case STFS_ITEM_LINK:
	case STFS_ITEM_DB_MEMBER:
		stbuf->st_mode = S_IFLNK | 0777;
		stbuf->st_nlink = 1;
		break;
	default:
		res = -ENOENT;
	}

	return res;

}

static int stfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi,
			 enum fuse_readdir_flags flags)
{
	stcore_filesystem_path base;
	const stfs_item *root = NULL;

	root = stfs_find_item_by_path(path);
	if (!root)
		return -ENOENT;

	filler(buf, ".", NULL, 0, FUSE_FILL_DIR_DEFAULTS);
	filler(buf, "..", NULL, 0, FUSE_FILL_DIR_DEFAULTS);
	DYNARRAY_INLINE_FOREACH(root->arg.dir_list, stfs_item) {
		stcore_filesystem_path_basename((*it)->fs_path, &base);
		filler(buf, base.target, NULL, 0, FUSE_FILL_DIR_DEFAULTS);
	}

	return 0;
}

static int stfs_readlink(const char *fpath, char *target, size_t len) {
	const stfs_item *i;

	i = stfs_find_item_by_path(fpath);
	if (!i)
		return -ENOENT;

	if (i->type != STFS_ITEM_LINK)
		return -EINVAL;

	strncpy(target, i->arg.link, len);

	return 0;
}

static int stfs_open(const char *fpath, struct fuse_file_info *fi) {
	// TODO: NOT IMPLEMENTED
	return -ENOENT;
}

static int stfs_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi)
{
	// TODO: NOT IMPLEMENTED
	return -ENOENT;
}

static void *stfs_init(struct fuse_conn_info *conn, struct fuse_config *cfg) {
	cfg->kernel_cache = 1;

	chdir(options.stpath);

	printf("STFS is ready...\n");
	return NULL;
}

static void stfs_destroy(void *_ /*unused*/) {
	free_dynarray(fs_dirs, NULL);
	free_dynarray(fs_items, (dynarray_free_cb)stfs_item_free);
}

static const struct fuse_operations stfs_oper = {
	.getattr = stfs_getattr,
	.readlink = stfs_readlink,
	.open = stfs_open,
	.read = stfs_read,
	.readdir = stfs_readdir,

	.init = stfs_init,
	.destroy = stfs_destroy,
};

static DLTX *stfs_load_from_cache(const char cache[]) {
	DLTX *r = NULL;
	DLTX_RETURN_CODE ret;

	printf("Using cache file to setup STFS...\n");
	r = dltx_create_from_file(cache, &ret);
	if (ret != NO_ERROR) {
		printf("Failed to read cache file...\n");
		return NULL;
	}
	stfs_cfg        = dltx_find_section(r, sec_cfg_name);
	stfs_map        = dltx_find_section(r, sec_map_name);
	stfs_db_preload = dltx_find_section(r, sec_preload_name);

	return r;
}

static DLTX *stfs_create_config(const char cache[]) {
	DLTX *r = NULL;

	r = dltx_create();

	stfs_cfg        = dltx_create_new_section(r, sec_cfg_name);
	stfs_map        = dltx_create_new_section(r, sec_map_name);
	stfs_db_preload = dltx_create_new_section(r, sec_preload_name);

	dltx_section_set_key(stfs_cfg, "wdir", options.stpath);

	parse_db_overrides();
	parse_cur_fs();

	if (options.use_cache)
		write_to_file(r, cache);

	return r;
}

static stfs_item *stfs_create_dir_if_dont_exist(const stcore_filesystem_path p) {
	stfs_item *i, *j;
	stcore_filesystem_path dir, pabs;

	if (stcore_filesystem_path_is_absolute(p)) {
		stcore_filesystem_path_copy(p, &dir);
	} else {
		stcore_filesystem_path_init(&dir, "/");
		stcore_filesystem_path_append(p, &dir);
	}

	DYNARRAY_INLINE_FOREACH(fs_dirs, stfs_item) {
		if (stcore_filesystem_path_equal((*it)->fs_path, dir))
			return *it;
	}

	i = stfs_item_create_dir(dir);

	stcore_filesystem_path_dirname(dir, &pabs);

	j = stfs_create_dir_if_dont_exist(pabs);
	dynarray_insert(j->arg.dir_list, i);

	return i;
}

static char create_buffer[PATH_MAX];
static const char *_stfs_create_arg_or_something(const char *arg, const char *p) {
	if (arg && *arg != 0)
		return arg;

	memset(create_buffer, 0, PATH_MAX);

	strcpy(create_buffer, dltx_section_get_key(stfs_cfg, "wdir")->value);
	strcat(create_buffer, "/");
	strcat(create_buffer, p);
	return create_buffer;
}

static void stfs_create_fs_structure(DLTX *config) {
	stfs_item *item, *dir;
	const DLTXSection *mapping;
	stcore_filesystem_path fsroot, dirname;

	mapping = dltx_find_section(config, "mapping");
	if (!mapping)
		return;

	fs_dirs = dynarray_create(128);
	fs_items = dynarray_create(stfs_map->keys->size + 512); // Allocate member number + 512 dirs to be safe

	stcore_filesystem_path_init(&fsroot, "/");
	stfs_item_create_dir(fsroot);  // Create root

	DYNARRAY_INLINE_FOREACH(mapping->keys, const DLTXKey) {
		item = malloc(sizeof(stfs_item));
		stfs_item_init(item, (*it)->name, _stfs_create_arg_or_something((*it)->value, (*it)->name));
		dynarray_insert(fs_items, item);

		stcore_filesystem_path_dirname(item->fs_path, &dirname);
		dir = stfs_create_dir_if_dont_exist(dirname);
		if (!dir)
			continue;

		dynarray_insert(dir->arg.dir_list, item);
	}

	qsort(fs_dirs->arr, fs_dirs->size, sizeof(stfs_item*), (int (*)(const void*, const void*))&stfs_item_sort);
	qsort(fs_items->arr, fs_items->size, sizeof(stfs_item*), (int (*)(const void*, const void*))&stfs_item_sort);

	free_dltx(config);
}

int main(int argc, char *argv[]) {
	struct stat s = {0};
	DLTX *stfs_root = NULL;
	struct fuse_args args __attribute__((cleanup(fuse_opt_free_args))) = FUSE_ARGS_INIT(argc, argv);

	if (fuse_opt_parse(&args, &options, option_spec, NULL) == -1)
		return 1;

	if (!options.stcache)
		options.stcache = strdup(stfs_default_cache_filename);

	if (dltx_init_code != NO_ERROR) {
		fprintf(stderr, "DLTX lib failed to init, aborting...\n");
		return -1;
	}

	if (options.show_help) {
		show_help(argv[0]);
		fuse_opt_add_arg(&args, "--help");
		args.argv[0][0] = '\0';

		return fuse_main(args.argc, args.argv, &stfs_oper, NULL);
	}

	chdir(options.stpath);

	if (filesystem_init("./fsgame.ltx") != 0) {
		fprintf(stderr, "Failed to init FS part of stcore, aborting...\n");
		return -1;
	}

	stcore_filesystem_path_init(&root_path, "/");

	// Parsing config and pre-setup
	stfs_root = ((options.use_cache && stat(options.stcache, &s) == 0) ?
	  stfs_load_from_cache :
	  stfs_create_config
	)(options.stcache);

	stfs_create_fs_structure(stfs_root);

	return fuse_main(args.argc, args.argv, &stfs_oper, NULL);
}
