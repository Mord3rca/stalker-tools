#include <stdlib.h>

#include "dynarray.h"

struct dynarray *dynarray_create(int size) {
	struct dynarray *o = malloc(sizeof(struct dynarray));

	o->size = 0;
	o->max_size = size;
	o->arr = calloc(sizeof(void*), o->max_size);

	return o;
}

void free_dynarray(struct dynarray *o, void (*free_item)(void*)) {
	void **cur, **end;

	if (free_item != NULL) {
		for(cur = o->arr, end = o->arr + o->size; cur < end; cur++)
			free_item(*cur);
	}

	free(o->arr);
	free(o);
}

void dynarray_foreach(struct dynarray *array, bool (*callback)(void*)) {
	void **cur, **end;

	for (cur = array->arr, end = array->arr + array->size; cur < end; cur++)
		if (! callback(*cur))
			break;
}


int dynarray_insert(struct dynarray *array, void *obj) {
	size_t nsize;

	if (array->size >= array->max_size) {
		nsize = array->max_size + 64;
		array->arr = reallocarray(array->arr, array->size, nsize);
		array->max_size = nsize;
	}

	array->arr[array->size++] = obj;
	return 0;
}

int dynarray_remove(struct dynarray *array, void *obj) {
	size_t pos;

	pos = dynarray_find_member_index(array, obj);
	if (pos == -1) {
		return -1;
	}

	array->size--;
	array->arr[pos] = array->arr[array->size];

	return 0;
}

size_t dynarray_find_member_index(struct dynarray *array, void *member) {
	bool found;
	size_t pos = -1;

	// Nobody will read this, it's fine !
	bool iterator(void *o) {
		found = o == member;
		pos++;
		return !found;
	}

	dynarray_foreach(array, &iterator);

	return found ? pos : -1;
}

void *dynarray_find(struct dynarray *array, bool (*callback)(void*)) {
	void *result = NULL;

	bool iterator(void *o) {
		if (callback(o)) {
			result = o;
			return false; // Stop iteration
		}

		return true;
	}

	dynarray_foreach(array, &iterator);
	return result;
}
