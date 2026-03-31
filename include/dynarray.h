#ifndef DYNAMIC_ARRAY_HEADER
#define DYNAMIC_ARRAY_HEADER

#include <stdbool.h>

struct dynarray {
	void **arr;
	size_t size;
	size_t max_size;
};

struct dynarray *dynarray_create(int);
void free_dynarray(struct dynarray*, void (*)(void*));

// Iterator
void dynarray_foreach(struct dynarray*, bool (*)(void*));

// Member manupulation
int dynarray_insert(struct dynarray*, void*);
int dynarray_remove(struct dynarray*, void*);

// Search
void *dynarray_find(struct dynarray*, bool (*)(void*));
size_t dynarray_find_member_index(struct dynarray*, void*);

#endif //DYNAMIC_ARRAY_HEADER
