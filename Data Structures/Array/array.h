#ifndef c_dsa_generic_array_h
#define c_dsa_generic_array_h


#include "stddef.h"

typedef struct {
   size_t size;
   size_t element_size;
   void* data;
   void (*destroyer)(void*);
} array;

void __check_range(array* arr, void* start, void* end);

array array_init_with_destroyer(size_t size, size_t element_size, void (*destroyer)(void*));

array arr_init(size_t size, size_t element_size);

void arr_for_each_idx(array* arr, void (*callback)(void*, size_t));

void arr_for_each(array* arr, void (*callback)(void*));

void arr_for_each_n_idx(array* arr, void* start, size_t n, void (*callback)(void*, size_t));

void arr_for_each_n(array* arr, void* start, size_t n, void (*callback)(void*));

void arr_for_each_rng_idx(array* arr, void* start, void* end, void (*callback)(void*, size_t));

void arr_for_each_rng(array* arr, void* start, void* end, void (*callback)(void*));

void arr_map_idx(array* arr, void (*callback)(void*, size_t));

void arr_map(array* arr, void (*callback)(void*));

void arr_map_n_idx(array* arr, void* start, size_t n, void (*callback)(void*, size_t));

void arr_map_n(array* arr, void* start, size_t n, void (*callback)(void*));

void arr_map_rng_idx(array* arr, void* start, void* end, void (*callback)(void*, size_t));

void arr_map_rng(array* arr, void* start, void* end, void (*callback)(void*));

void* arr_find(array* arr, void* data);

void* arr_find_rng(array* arr, void* start, void* end, void* data);

void* arr_find_n(array* arr, void* start, size_t n, void* data);

void* arr_find_if(array* arr, int (*predicate)(void*));

void* arr_find_if_rng(array* arr, void* start, void* end, int (*predicate)(void*));

void* arr_find_if_n(array* arr, void* start, size_t n, int (*predicate)(void*));

void* arr_find_if_not(array* arr, int (*predicate)(void*));

void* arr_find_if_not_rng(array* arr, void* start, void* end, int (*predicate)(void*));

void* arr_find_if_not_n(array* arr, void* start, size_t n, int (*predicate)(void*));

void _arr_destroyer(array* arr);

void arr_free(array* arr);

void arr_clear(array* arr);

void* arr_begin(array* arr);

void* arr_end(array* arr);

void* arr_front(array* arr);

void* arr_back(array* arr);

void arr_fill_rng(array* arr, void* start, void* end, void* data);

void arr_fill(array* arr, void* data);

void arr_fill_n(array* arr, void* start, size_t n, void* data);

void* arr_at(array* arr, int idx);

void arr_reverse(array* arr);

void arr_reverse_n(array* arr, void* start, size_t n);

void arr_reverse_rng(array* arr, void* start, void* end);

void arr_sort_cmp(array* arr, int (*cmp)(void*, void*));

void arr_sort(array* arr);

void arr_sort_n_cmp(array* arr, void* start, size_t n, int (*cmp)(void*, void*));

void arr_sort_n(array* arr, void* start, size_t n);

void arr_sort_rng_cmp(array* arr, void* start, void* end, int (*cmp)(void*, void*));

void arr_sort_rng(array* arr, void* start, void* end);

void* arr_at(array* arr, int idx);





#endif // c_dsa_generic_array
