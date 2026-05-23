#ifndef DYNAMIC_ARRAY_HEADER
#define DYNAMIC_ARRAY_HEADER

#include <stdbool.h>

struct dynarray {
	void **arr;
	size_t size;
	size_t max_size;
};

typedef bool (*dynarray_cb)(void*, void*);
typedef void (*dynarray_free_cb)(void*);

struct dynarray *dynarray_create(int);
void free_dynarray(struct dynarray*, dynarray_free_cb);

// Iterator
void dynarray_foreach(struct dynarray*, dynarray_cb, void*);

// Member manupulation
int dynarray_insert(struct dynarray*, void*);
int dynarray_remove(struct dynarray*, void*);

// Search
void *dynarray_find(struct dynarray*, dynarray_cb, void*);
size_t dynarray_find_member_index(struct dynarray*, void*);

#endif //DYNAMIC_ARRAY_HEADER
