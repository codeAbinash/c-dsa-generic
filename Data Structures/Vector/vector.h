#ifndef c_dsa_generic_vector_h
#define c_dsa_generic_vector_h

#include "stddef.h"

/**
 * @brief A generic vector data structure.
 * @var size_t size The number of elements in the vector.
 * @var size_t element_size The size of each element in the vector.
 * @var size_t capacity The number of elements the vector can hold before it needs to be resized.
 * @var void* data A pointer to the data in the vector.
 * @var void (*destroyer)(void*) A function pointer to a function that destroys the data
 * allocated by the user in the vector. It is called when a vector is removed using library functions.
*/
typedef struct vector {
   size_t size;
   size_t element_size;
   size_t capacity;
   void* data;
   void (*destroyer)(void*);
} vector;


vector vec_init_with_destroyer(size_t size, size_t element_size, void (*destroyer)(void*));
vector vec_init(size_t size, size_t element_size);
size_t vec_capacity(vector* vec);
size_t vec_size(vector* vec);
size_t vec_max_size(vector* vec);
size_t vec_element_size(vector* vec);
int vec_empty(vector* vec);
void* vec_begin(vector* vec);
void* vec_end(vector* vec);
void* vec_front(vector* vec);
void* vec_back(vector* vec);
void __check_range(vector* vec, void* start, void* end);
void vec_for_each_idx(vector* vec, void (*callback)(void*, size_t));
void vec_for_each(vector* vec, void (*callback)(void*));
void vec_for_each_n_idx(vector* vec, void* start, size_t n, void (*callback)(void*, size_t));
void vec_for_each_n(vector* vec, void* start, size_t n, void (*callback)(void*));
void vec_for_each_rng_idx(vector* vec, void* start, void* end, void (*callback)(void*, size_t));
void vec_for_each_rng(vector* vec, void* start, void* end, void (*callback)(void*));
void vec_map_idx(vector* vec, void (*callback)(void*, size_t));
void vec_map(vector* vec, void (*callback)(void*));
void vec_map_n_idx(vector* vec, void* start, size_t n, void (*callback)(void*, size_t));
void vec_map_n(vector* vec, void* start, size_t n, void (*callback)(void*));
void vec_map_rng_idx(vector* vec, void* start, void* end, void (*callback)(void*, size_t));
void vec_map_rng(vector* vec, void* start, void* end, void (*callback)(void*));
void* vec_find(vector* vec, void* data);
void* vec_find_rng(vector* vec, void* start, void* end, void* data);
void* vec_find_n(vector* vec, void* start, size_t n, void* data);
void* vec_find_if(vector* vec, int (*predicate)(void*));
void* vec_find_if_rng(vector* vec, void* start, void* end, int (*predicate)(void*));
void* vec_find_if_n(vector* vec, void* start, size_t n, int (*predicate)(void*));
void* vec_find_if_not(vector* vec, int (*predicate)(void*));
void* vec_find_if_not_rng(vector* vec, void* start, void* end, int (*predicate)(void*));
void* vec_find_if_not_n(vector* vec, void* start, size_t n, int (*predicate)(void*));
void vec_reverse(vector* vec);
void vec_reverse_n(vector* vec, void* start, size_t n);
void vec_reverse_rng(vector* vec, void* start, void* end);
void vec_sort_cmp(vector* vec, int (*cmp)(void*, void*));
void vec_sort(vector* vec);
void vec_sort_n_cmp(vector* vec, void* start, size_t n, int (*cmp)(void*, void*));
void vec_sort_n(vector* vec, void* start, size_t n);
void vec_sort_rng_cmp(vector* vec, void* start, void* end, int (*cmp)(void*, void*));
void vec_sort_rng(vector* vec, void* start, void* end);
void vec_fill_rng(vector* vec, void* start, void* end, void* data);
void vec_fill(vector* vec, void* data);
void vec_fill_n(vector* vec, void* start, size_t n, void* data);
void* vec_at(vector* vec, int index);
void __vec_destroy_rng(vector* vec, void* start, void* end);
void __vec_destroy_each_item(vector* vec);
void __vec_destroyer(vector* vec);
void vec_free(vector* vec);
void vec_clear(vector* vec);
void __force_reserve_to(vector* vec, size_t size);
void __force_resize_to(vector* vec, size_t size);
void vec_resize(vector* vec, size_t size);
void vec_reserve(vector* vec, size_t size);
void vec_shrink_to_fit(vector* vec);
void vec_pop_back(vector* vec);
void vec_assign(vector* vec, size_t n, void* data);
void vec_assign_rng(vector* vec, void* start, void* end);
void __vec_double_if_full(vector* vec);
void vec_push_back(vector* vec, void* data);
void __valid_pos(vector* vec, void* pos);
void __check_erase_bounds(vector* vec, void* start, void* end);
void vec_erase_rng(vector* vec, void* start, void* end);
void vec_erase(vector* vec, void* pos);
void vec_insert(vector* vec, void* pos, void* data);
void vec_insert_rng(vector* vec, void* pos, void* start, void* end);






#endif // c_dsa_generic_vector_h
