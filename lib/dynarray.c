#include <stdlib.h>

#include "dynarray.h"

struct dynarray *dynarray_create(int size)
{
	struct dynarray *o = malloc(sizeof(struct dynarray));

	o->size = 0;
	o->max_size = size;
	o->arr = calloc(o->max_size, sizeof(void *));

	return o;
}

static bool _free_iterator(void *m, dynarray_free_cb free_callback)
{
	free_callback(m);
	return true;
}

void free_dynarray(struct dynarray *o, dynarray_free_cb free_item)
{
	if (!o)
		return;

	if (free_item != NULL)
		dynarray_foreach(o, (dynarray_cb)&_free_iterator, free_item);

	free(o->arr);
	free(o);
}

void dynarray_foreach(struct dynarray *array, dynarray_cb callback, void *data)
{
	void **cur, **end;

	for (cur = array->arr, end = array->arr + array->size; cur < end; cur++)
		if (!callback(*cur, data))
			break;
}


int dynarray_insert(struct dynarray *array, void *obj)
{
	size_t nsize;

	if (array->size >= array->max_size) {
		nsize = array->max_size + 64;
		array->arr = reallocarray(array->arr, array->size, nsize);
		array->max_size = nsize;
	}

	array->arr[array->size++] = obj;
	return 0;
}

int dynarray_remove(struct dynarray *array, void *obj)
{
	size_t pos;

	pos = dynarray_find_member_index(array, obj);
	if (pos == -1)
		return -1;

	array->size--;
	array->arr[pos] = array->arr[array->size];

	return 0;
}

struct _find_member_index_args {
	size_t pos;
	void *member;
	bool found;
};

static bool _find_member_iterator(void *o, struct _find_member_index_args *args)
{
	args->found = o == args->member;
	args->pos++;
	return !args->found;
}

size_t dynarray_find_member_index(struct dynarray *array, void *member)
{
	struct _find_member_index_args args;

	args.pos = -1;
	args.found = false;
	args.member = member;

	dynarray_foreach(array, (dynarray_cb)&_find_member_iterator, (void *)&args);

	return args.found ? args.pos : -1;
}

struct _find_iterator_args {
	void *data;
	void *result;
	dynarray_cb callback;
};

static bool _dynarray_find_iterator(void *o, struct _find_iterator_args *args)
{
	if (args->callback(o, args->data)) {
		args->result = o;
		return false;
	}
	return true;
}

void *dynarray_find(struct dynarray *array, dynarray_cb callback, void *data)
{
	struct _find_iterator_args args;

	args.data = data;
	args.result = NULL;
	args.callback = callback;

	dynarray_foreach(array, (dynarray_cb)&_dynarray_find_iterator, (void *)&args);
	return args.result;
}
