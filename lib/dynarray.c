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

void dynarray_free(struct dynarray *o, dynarray_free_cb free_item)
{
	if (!o)
		return;

	if (free_item != NULL)
		DYNARRAY_INLINE_FOREACH(o, void)
			free_item(*it);

	free(o->arr);
	free(o);
}

int dynarray_reserve(struct dynarray *array, size_t nsize)
{
	if (nsize < array->max_size)
		return -1;

	if (array->size == 0) {
		free(array->arr);
		array->arr = calloc(nsize, sizeof(void *));
	} else
		array->arr = reallocarray(array->arr, array->size, nsize);

	array->max_size = nsize;

	return 0;
}

void dynarray_foreach(struct dynarray *array, dynarray_cb callback, void *data)
{
	DYNARRAY_INLINE_FOREACH(array, void)
		if (!callback(*it, data))
			break;
}


int dynarray_insert(struct dynarray *array, void *obj)
{
	if (array->size >= array->max_size)
		if (dynarray_reserve(array, array->max_size + 64) < 0)
			return -1;

	array->arr[array->size++] = obj;
	return 0;
}

int dynarray_remove(struct dynarray *array, void *obj)
{
	size_t pos;

	if (!array)
		return -1;

	pos = dynarray_find_member_index(array, obj);
	if (pos == -1)
		return -1;

	array->size--;
	array->arr[pos] = array->arr[array->size];

	return 0;
}

size_t dynarray_find_member_index(struct dynarray *array, void *member)
{
	size_t r = 0;

	if (!array || !member)
		return -1;

	DYNARRAY_INLINE_FOREACH(array, void) {
		if (*it == member)
			return r;
		r++;
	}

	return -1;
}

void *dynarray_find(struct dynarray *array, dynarray_cb callback, void *data)
{
	if (!array)
		return NULL;

	DYNARRAY_INLINE_FOREACH(array, void)
		if (callback(*it, data))
			return *it;

	return NULL;
}
