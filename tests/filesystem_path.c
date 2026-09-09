#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "filesystem_path.h"

static const char t[] = "/path/to/a/file";

char *path_canonicalize_test;
stcore_filesystem_path *path_create_test;
stcore_filesystem_path *path_sys_create_test;

enum {
	IDX_PATH1 = 0,
	IDX_PATH1_BASENAME = 1,
	IDX_PATH1_DIRNAME,

	IDX_PATH2,
	IDX_PATH2_BASENAME,
	IDX_PATH2_DIRNAME,

	IDX_PATH3,
	IDX_PATH3_BASENAME,
	IDX_PATH3_DIRNAME,

	IDX_PATH4,
	IDX_PATH4_BASENAME,
	IDX_PATH4_DIRNAME,

	IDX_PATH_APPEND1,
	IDX_PATH_APPEND2,

	IDX_PATH_PREPEND1,
	IDX_PATH_PREPEND2,

	IDX_PATH_SIZE
} path_idx;

stcore_filesystem_path paths[IDX_PATH_SIZE];

static void test_fs_path_init(void)
{
	stcore_filesystem_path path;

	stcore_filesystem_path_init(&path, t);

	CU_ASSERT_EQUAL(path.len, 15);
	CU_ASSERT_EQUAL(path.scount, 4);
	CU_ASSERT_EQUAL(path.last_sep_offset, 10);
	CU_ASSERT_EQUAL(strncmp(path.target, t, strlen(t)), 0);
}

static void test_fs_path_create(void)
{
	path_create_test = stcore_filesystem_path_create(t);

	CU_ASSERT_NOT_EQUAL(path_create_test, NULL);

	CU_ASSERT_EQUAL(path_create_test->len, 15);
	CU_ASSERT_EQUAL(path_create_test->scount, 4);
	CU_ASSERT_EQUAL(path_create_test->last_sep_offset, 10);
	CU_ASSERT_EQUAL(strncmp(path_create_test->target, t, strlen(path_create_test->target)), 0);
}

static void test_fs_path_copy(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_copy(&p, paths[IDX_PATH1]);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH1]));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH1_BASENAME]);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH1_BASENAME]));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH1_DIRNAME]);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH1_DIRNAME]));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2]);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH2]));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2_BASENAME]);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH2_BASENAME]));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2_DIRNAME]);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH2_DIRNAME]));
}

static void test_fs_path_cmp(void)
{
	CU_ASSERT(stcore_filesystem_path_cmp(paths[IDX_PATH1], paths[IDX_PATH2]) > 0);
	CU_ASSERT(stcore_filesystem_path_cmp(paths[IDX_PATH1], paths[IDX_PATH1_BASENAME]) > 0);
	CU_ASSERT(stcore_filesystem_path_cmp(paths[IDX_PATH1], paths[IDX_PATH1_DIRNAME]) > 0);

	CU_ASSERT(stcore_filesystem_path_cmp(paths[IDX_PATH2], paths[IDX_PATH4]) > 0);
	CU_ASSERT(stcore_filesystem_path_cmp(paths[IDX_PATH2], paths[IDX_PATH2_BASENAME]) > 0);
	CU_ASSERT(stcore_filesystem_path_cmp(paths[IDX_PATH2], paths[IDX_PATH2_DIRNAME]) > 0);

	CU_ASSERT(stcore_filesystem_path_cmp(paths[IDX_PATH4], paths[IDX_PATH2]) < 0);

}

static void test_fs_path_equal(void)
{
	stcore_filesystem_path p;

	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH1], paths[IDX_PATH1]));
	CU_ASSERT(!stcore_filesystem_path_equal(paths[IDX_PATH1], paths[IDX_PATH2]));

	stcore_filesystem_path_init(&p, paths[IDX_PATH2].target);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH2], p));
}

static void test_fs_path_is_absolute(void)
{
	CU_ASSERT(stcore_filesystem_path_is_absolute(paths[IDX_PATH1]));
	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH1_BASENAME]));
	CU_ASSERT(stcore_filesystem_path_is_absolute(paths[IDX_PATH1_DIRNAME]));

	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH2]));
	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH2_BASENAME]));
	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH2_DIRNAME]));

	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH3]));
	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH3_BASENAME]));
	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH3_DIRNAME]));

	CU_ASSERT(stcore_filesystem_path_is_absolute(paths[IDX_PATH4]));
	CU_ASSERT(!stcore_filesystem_path_is_absolute(paths[IDX_PATH4_BASENAME]));
	CU_ASSERT(stcore_filesystem_path_is_absolute(paths[IDX_PATH4_DIRNAME]));
}

static void test_fs_path_dirname(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_copy(&p, paths[IDX_PATH1]);
	stcore_filesystem_path_dirname(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH1_DIRNAME], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2]);
	stcore_filesystem_path_dirname(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH2_DIRNAME], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH3]);
	stcore_filesystem_path_dirname(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH3_DIRNAME], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH4]);
	stcore_filesystem_path_dirname(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH4_DIRNAME], p));
}

static void test_fs_path_basename(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_copy(&p, paths[IDX_PATH1]);
	stcore_filesystem_path_basename(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH1_BASENAME], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2]);
	stcore_filesystem_path_basename(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH2_BASENAME], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH3]);
	stcore_filesystem_path_basename(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH3_BASENAME], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH4]);
	stcore_filesystem_path_basename(&p);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH4_BASENAME], p));
}

static void test_fs_path_append(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2]);
	stcore_filesystem_path_append(&p, paths[IDX_PATH4]);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_APPEND1], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH3]);
	stcore_filesystem_path_append(&p, paths[IDX_PATH1]);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_APPEND2], p));
}

static void test_fs_path_append2(void)
{
	stcore_filesystem_path p, q;

	stcore_filesystem_path_init(&q, "/path/to/home");
	stcore_filesystem_path_append2(&p, paths[IDX_PATH1].target, paths[IDX_PATH3].target);
	CU_ASSERT(stcore_filesystem_path_equal(p, q));
}

static void test_fs_path_prepend(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_copy(&p, paths[IDX_PATH1_BASENAME]);
	stcore_filesystem_path_prepend(&p, paths[IDX_PATH4]);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_PREPEND1], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2_DIRNAME]);
	stcore_filesystem_path_prepend(&p, paths[IDX_PATH1]);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_PREPEND2], p));
}

static void test_fs_path_append_str(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2]);
	stcore_filesystem_path_append_str(&p, paths[IDX_PATH4].target);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_APPEND1], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH3]);
	stcore_filesystem_path_append_str(&p, paths[IDX_PATH1].target);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_APPEND2], p));
}

static void test_fs_path_prepend_str(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_copy(&p, paths[IDX_PATH1_BASENAME]);
	stcore_filesystem_path_prepend_str(&p, paths[IDX_PATH4].target);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_PREPEND1], p));

	stcore_filesystem_path_copy(&p, paths[IDX_PATH2_DIRNAME]);
	stcore_filesystem_path_prepend_str(&p, paths[IDX_PATH1].target);
	CU_ASSERT(stcore_filesystem_path_equal(paths[IDX_PATH_PREPEND2], p));
}

static void test_fs_path_to_system(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_init(&p, "relative\\path");
	stcore_filesystem_path_to_system(&p);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH2]));
}

static void test_fs_path_to_lower(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_init(&p, "/PaTH/TO/File");
	stcore_filesystem_path_to_lower(&p);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH1]));
}

static void test_fs_path_create_to_system(void)
{
	path_sys_create_test = stcore_filesystem_path_create_to_system("\\path\\to\\file");
	CU_ASSERT(stcore_filesystem_path_equal(*path_sys_create_test, paths[IDX_PATH1]));
}

static void test_fs_path_canonicalize(void)
{
	stcore_filesystem_path p;

	stcore_filesystem_path_init(&p, "//./path//to/file//");
	stcore_filesystem_path_canonicalize(&p);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH1]));

	stcore_filesystem_path_init(&p, "./file");
	stcore_filesystem_path_canonicalize(&p);
	CU_ASSERT(stcore_filesystem_path_equal(p, paths[IDX_PATH1_BASENAME]));
}

static void test_fs_path_canonicalize_str(void)
{
	char p[] = "//./path/to/file//.//";

	path_canonicalize_test = stcore_filesystem_path_canonicalize_str(p);
	CU_ASSERT(strcmp(path_canonicalize_test, paths[IDX_PATH1].target) == 0);
}

// Exported functions

int fs_path_init(void)
{
	stcore_filesystem_path_init(paths + IDX_PATH1, "/path/to/file");
	stcore_filesystem_path_init(paths + IDX_PATH1_BASENAME, "file");
	stcore_filesystem_path_init(paths + IDX_PATH1_DIRNAME, "/path/to");

	stcore_filesystem_path_init(paths + IDX_PATH2, "relative/path");
	stcore_filesystem_path_init(paths + IDX_PATH2_BASENAME, "path");
	stcore_filesystem_path_init(paths + IDX_PATH2_DIRNAME, "relative");

	stcore_filesystem_path_init(paths + IDX_PATH3, "home");
	stcore_filesystem_path_init(paths + IDX_PATH3_BASENAME, "home");
	stcore_filesystem_path_init(paths + IDX_PATH3_DIRNAME, ".");

	stcore_filesystem_path_init(paths + IDX_PATH4, "/root");
	stcore_filesystem_path_init(paths + IDX_PATH4_BASENAME, "root");
	stcore_filesystem_path_init(paths + IDX_PATH4_DIRNAME, "/");

	stcore_filesystem_path_init(paths + IDX_PATH_APPEND1, "relative/path/root");
	stcore_filesystem_path_init(paths + IDX_PATH_APPEND2, "home/path/to/file");

	stcore_filesystem_path_init(paths + IDX_PATH_PREPEND1, "/root/file");
	stcore_filesystem_path_init(paths + IDX_PATH_PREPEND2, "/path/to/file/relative");
	return 0;
}

int fs_path_cleanup(void)
{
	free(path_canonicalize_test);
	free(path_create_test);
	free(path_sys_create_test);
	return 0;
}

CU_TestInfo fs_path_tests[] = {
	{"init", test_fs_path_init},
	{"create", test_fs_path_create},

	{"copy", test_fs_path_copy},

	{"cmp", test_fs_path_cmp},
	{"equal", test_fs_path_equal},
	{"is_absolute", test_fs_path_is_absolute},

	{"dirname", test_fs_path_dirname},
	{"basename", test_fs_path_basename},

	{"append", test_fs_path_append},
	{"append2", test_fs_path_append2},
	{"prepend", test_fs_path_prepend},

	{"append_str", test_fs_path_append_str},
	{"prepend_str", test_fs_path_prepend_str},

	{"to_system", test_fs_path_to_system},
	{"to_lower", test_fs_path_to_lower},

	{"create_to_system", test_fs_path_create_to_system},

	{"canonicalize", test_fs_path_canonicalize},
	{"canonicalize_str", test_fs_path_canonicalize_str},
	CU_TEST_INFO_NULL,
};
