#include <CUnit/CUnit.h>
#include <stdbool.h>
#include <string.h>

#include "dynarray.h"

// Counter for various tests.
static size_t __ncall;

static int __int_items[] = {50, 30, 20, 100};
static size_t __int_items_size = sizeof(__int_items) / sizeof(int);

static struct dynarray *_create_from_int_dataset(void)
{
	struct dynarray *array;

	array = dynarray_create(__int_items_size);

	CU_ASSERT_FATAL(array != NULL);

	for (size_t i = 0; i < __int_items_size; i++)
		dynarray_insert(array, __int_items + i);

	return array;
}

static char *__char_items[] = {
	"foo",
	"bar",
	"foobar"
};
static size_t __char_items_size = sizeof(__char_items) / sizeof(char *);

static struct dynarray *_create_from_char_dataset(void)
{
	struct dynarray *array;

	array = dynarray_create(__char_items_size);

	CU_ASSERT_FATAL(array != NULL);

	for (size_t i = 0; i < __char_items_size; i++)
		dynarray_insert(array, __char_items + i);

	return array;
}


static void __dont_call_me(void *_)
{
	CU_ASSERT(false);
}

static void test_dynarray_create(void)
{
	struct dynarray *array;

	array = dynarray_create(8);

	CU_ASSERT_FATAL(array != NULL);
	CU_ASSERT_FATAL(array->arr != NULL);
	CU_ASSERT(array->size == 0);
	CU_ASSERT(array->max_size == 8);

	dynarray_free(array, &__dont_call_me);
}

static void __tfree(int *item)
{
	CU_ASSERT(
		(__int_items + __ncall) == item
	);
	__ncall++;
}

static void test_dynarray_free(void)
{
	struct dynarray *array;

	array = _create_from_int_dataset();

	__ncall = 0;
	dynarray_free(array, (dynarray_free_cb)&__tfree);

	CU_ASSERT(__ncall == 4);
}

static void test_dynarray_reserve(void)
{
	void **_arr;
	struct dynarray *array;

	array = dynarray_create(8);

	CU_ASSERT_FATAL(array != NULL);
	CU_ASSERT_FATAL(array->arr != NULL);
	CU_ASSERT(array->size == 0);
	CU_ASSERT(array->max_size == 8);

	_arr = array->arr;
	dynarray_reserve(array, 64);

	CU_ASSERT_FATAL(array->arr != NULL);
	CU_ASSERT(array->size == 0);
	CU_ASSERT(array->max_size == 64);

	dynarray_free(array, NULL);
}

static void test_dynarray_shrink(void)
{
	struct dynarray *array;

	array = dynarray_create(8);

	CU_ASSERT(dynarray_reserve(array, 4) < 0);

	dynarray_free(array, NULL);
}

static void test_dynarray_realloc(void)
{
	struct dynarray *array;

	array = dynarray_create(1);

	CU_ASSERT_FATAL(array != NULL);
	CU_ASSERT_FATAL(array->arr != NULL);
	CU_ASSERT(array->size == 0);
	CU_ASSERT(array->max_size == 1);

	for (size_t i = 0; i < __int_items_size; i++)
		dynarray_insert(array, __int_items + i);

	CU_ASSERT_FATAL(array->arr != NULL);
	CU_ASSERT(array->size == __int_items_size);
	CU_ASSERT(array->max_size >= __int_items_size);

	__ncall = 0;
	dynarray_free(array, (dynarray_free_cb)&__tfree);

	CU_ASSERT(__ncall == __int_items_size);
}

static int *__ctrl;
static bool __tforeach(void *a, void *ctrl)
{
	__ncall++;

	CU_ASSERT(ctrl == &__ctrl);

	return a != (__int_items + 2);
}

static void test_dynarray_foreach(void)
{
	struct dynarray *array;

	array = _create_from_int_dataset();

	__ncall = 0;
	dynarray_foreach(array, __tforeach, &__ctrl);

	CU_ASSERT(__ncall == 3);

	dynarray_free(array, NULL);
}

static int _insert_int;
static void _check_int_insert(void *a)
{
	if (__ncall == __int_items_size + 1)
		CU_ASSERT(a == &_insert_int);
	__ncall++;
}

static void test_dynarray_insert(void)
{
	struct dynarray *array = _create_from_int_dataset();

	CU_ASSERT(array->size = __int_items_size);

	CU_ASSERT(dynarray_insert(array, &_insert_int) == 0);

	CU_ASSERT(array->size = __int_items_size + 1);

	__ncall = 0;
	dynarray_free(array, &_check_int_insert);

	CU_ASSERT(__ncall == (__int_items_size + 1));
}

static void _check_removal(void *a)
{
	CU_ASSERT(a != (__int_items + __int_items_size - 1));
}

static void test_dynarray_remove(void)
{
	struct dynarray *array = _create_from_int_dataset();

	CU_ASSERT(dynarray_remove(array, (__int_items + __int_items_size - 1)) == 0);
	CU_ASSERT(array->size == (__int_items_size - 1));

	__ncall = 0;
	dynarray_free(array, &_check_removal);
}

static bool _find_str(const char **a, const char *b)
{
	return strcmp(*a, b) == 0;
}

static void test_dynarray_find(void)
{
	char **item;
	struct dynarray *array;

	array = _create_from_char_dataset();

	item = dynarray_find(array, (dynarray_cb)&_find_str, "bar");

	CU_ASSERT(item == (__char_items + 1));

	dynarray_free(array, NULL);
}

static void test_dynarray_find_member_index(void)
{
	size_t item_pos;
	struct dynarray *array;

	array = _create_from_char_dataset();

	item_pos = dynarray_find_member_index(array, __char_items + 2);

	CU_ASSERT(item_pos == 2);

	dynarray_free(array, NULL);
}

// Exported functions

int test_dynarray_init(void)
{
	return 0;
}

int test_dynarray_cleanup(void)
{
	return 0;
}

CU_TestInfo dynarray_tests[] = {
	{"create", test_dynarray_create},
	{"free", test_dynarray_free},
	{"reserve", test_dynarray_reserve},
	{"shrink", test_dynarray_shrink},
	{"realloc", test_dynarray_realloc},
	{"foreach", test_dynarray_foreach},
	{"insert", test_dynarray_insert},
	{"remove", test_dynarray_remove},
	{"find", test_dynarray_find},
	{"find_member_index", test_dynarray_find_member_index},
	CU_TEST_INFO_NULL
};
