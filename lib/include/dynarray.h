#ifndef DYNAMIC_ARRAY_HEADER
#define DYNAMIC_ARRAY_HEADER

#include <stdbool.h>

struct dynarray {
	void **arr;
	size_t size;
	size_t max_size;
};

typedef bool (*dynarray_cb)(void *, void *);
typedef void (*dynarray_free_cb)(void *);

#define DYNARRAY_INLINE_FOREACH(D, T) \
	for (T **it = (T **)D->arr, **itend = (T **)(D->arr + D->size); it < itend; it++)

struct dynarray *dynarray_create(int size);
void free_dynarray(struct dynarray *array, dynarray_free_cb free_item);

// Iterator
void dynarray_foreach(struct dynarray *array, dynarray_cb callback, void *data);

// Member manupulation
int dynarray_insert(struct dynarray *array, void *obj);
int dynarray_remove(struct dynarray *array, void *obj);

// Search
void *dynarray_find(struct dynarray *array, dynarray_cb callback, void *data);
size_t dynarray_find_member_index(struct dynarray *array, void *member);

#endif //DYNAMIC_ARRAY_HEADER
