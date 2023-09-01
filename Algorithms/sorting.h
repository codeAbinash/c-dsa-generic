#include "stddef.h"

#ifndef c_dsa_generic_util_sorting
#define c_dsa_generic_util_sorting

void selection_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*));

void quick_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*));

void merge_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*));

void insertion_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*));

void _heap_ify(void* start, size_t size, int i, size_t element_size, int (*cmp)(void*, void*));

void heap_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*));

void sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*));

#endif // c_dsa_generic_util_sorting