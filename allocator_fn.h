// header file 

#ifndef ALLOCATOR_FN_H
#define ALLOCATOR_FN_H

#include <stddef.h> 

void* my_malloc(size_t size);

void add_ref(void* ptr);

void release_ref(void* ptr);

void gc_collect(void);

#endif 