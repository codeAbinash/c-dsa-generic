#ifndef c_dsa_generic_algorithms_h
#define c_dsa_generic_algorithms_h
#define byte unsigned char

#include "stddef.h"


int int_cmp(void* a, void* b);

void fill(void* start, void* end, size_t element_size, void* value);

void fill_n(void* start, size_t n, size_t element_size, void* value);

void for_each_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t));

void for_each(void* start, void* end, size_t element_size, void (*callback)(void*));

void for_each_n_idx(void* start, size_t n, size_t element_size, void (*callback)(void*, size_t));

void for_each_n(void* start, size_t n, size_t element_size, void (*callback)(void*));

void for_each_rng_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t));

void for_each_rng(void* start, void* end, size_t element_size, void (*callback)(void*));

void map_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t));

void map(void* start, void* end, size_t element_size, void (*callback)(void*));

void map_n_idx(void* start, size_t n, size_t element_size, void (*callback)(void*, size_t));

void map_n(void* start, size_t n, size_t element_size, void (*callback)(void*));

void map_rng_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t));

void map_rng(void* start, void* end, size_t element_size, void (*callback)(void*));

void* find_cmp(void* start, void* end, size_t element_size, void* value, int (*cmp)(void*, void*, size_t));

void* find(void* start, void* end, size_t element_size, void* value);

void* find_n_cmp(void* start, size_t n, size_t element_size, void* value, int (*cmp)(void*, void*, size_t));

void* find_n(void* start, size_t n, size_t element_size, void* value);

void* find_rng_cmp(void* start, void* end, size_t element_size, void* value, int (*cmp)(void*, void*, size_t));

void* find_rng(void* start, void* end, size_t element_size, void* value);

void* find_if(void* start, void* end, size_t element_size, int (*predicate)(void*));

void* find_if_n(void* start, size_t n, size_t element_size, int (*predicate)(void*));

void* find_if_rng(void* start, void* end, size_t element_size, int (*predicate)(void*));

void* find_if_not(void* start, void* end, size_t element_size, int (*predicate)(void*));

void* find_if_not_n(void* start, size_t n, size_t element_size, int (*predicate)(void*));

void* find_if_not_rng(void* start, void* end, size_t element_size, int (*predicate)(void*));

void* reverse(void* start, void* end, size_t element_size);

void* reverse_n(void* start, size_t n, size_t element_size);

void* reverse_rng(void* start, void* end, size_t element_size);

void swap(void* a, void* b, size_t element_size);




#endif // c_dsa_generic_util
