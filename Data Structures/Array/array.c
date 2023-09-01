/**
 * Library for array data structure
 * Author : Abinash Karmakar
 * 2023-08-29 MIT License Version: 1.0
*/

#include "stddef.h"
#include "assert.h"
#include "array.h"
#include "malloc.h"
#include "../../Algorithms/algorithms.h"
#include "../../Algorithms/algorithms.c" // TODO: Remove this



void __check_range(array* arr, void* start, void* end) {
   assert(start >= arr->data && "Start pointer out of bounds");
   assert(end <= arr->data + arr->size * arr->element_size && "End pointer out of bounds");
   assert(start <= end && "Start pointer must be less than or equal to end pointer");
   assert((end - start) % arr->element_size == 0 && "Invalid range");
}

array array_init_with_destroyer(size_t size, size_t element_size, void (*destroyer)(void*)) {
   assert(size > 0 && "Array size must be greater than 0");
   array arr;
   arr.size = size;
   arr.element_size = element_size;
   arr.data = malloc(size * element_size);
   arr.destroyer = destroyer;
   return arr;
}


array arr_init(size_t size, size_t element_size) {
   return array_init_with_destroyer(size, element_size, NULL);
}


void arr_for_each_idx(array* arr, void (*callback)(void*, size_t)) {
   void* start = arr->data;
   void* end = arr->data + arr->size * arr->element_size;
   for_each_idx(start, end, arr->element_size, callback);
}


void arr_for_each(array* arr, void (*callback)(void*)) {
   arr_for_each_idx(arr, (void (*)(void*, size_t))callback);
}


void arr_for_each_n_idx(array* arr, void* start, size_t n, void (*callback)(void*, size_t)) {
   __check_range(arr, start, start + n * arr->element_size);
   for_each_n_idx(start, n, arr->element_size, callback);
}


void arr_for_each_n(array* arr, void* start, size_t n, void (*callback)(void*)) {
   arr_for_each_n_idx(arr, start, n, (void (*)(void*, size_t))callback);
}


void arr_for_each_rng_idx(array* arr, void* start, void* end, void (*callback)(void*, size_t)) {
   __check_range(arr, start, end);
   for_each_rng_idx(start, end, arr->element_size, callback);
}


void arr_for_each_rng(array* arr, void* start, void* end, void (*callback)(void*)) {
   arr_for_each_rng_idx(arr, start, end, (void (*)(void*, size_t))callback);
}


void arr_map_idx(array* arr, void (*callback)(void*, size_t)) {
   void* start = arr->data;
   void* end = arr->data + arr->size * arr->element_size;
   map_idx(start, end, arr->element_size, callback);
}


void arr_map(array* arr, void (*callback)(void*)) {
   arr_map_idx(arr, (void (*)(void*, size_t))callback);
}


void arr_map_n_idx(array* arr, void* start, size_t n, void (*callback)(void*, size_t)) {
   __check_range(arr, start, start + n * arr->element_size);
   map_n_idx(start, n, arr->element_size, callback);
}


void arr_map_n(array* arr, void* start, size_t n, void (*callback)(void*)) {
   arr_map_n_idx(arr, start, n, (void (*)(void*, size_t))callback);
}


void arr_map_rng_idx(array* arr, void* start, void* end, void (*callback)(void*, size_t)) {
   __check_range(arr, start, end);
   map_rng_idx(start, end, arr->element_size, callback);
}


void arr_map_rng(array* arr, void* start, void* end, void (*callback)(void*)) {
   arr_map_rng_idx(arr, start, end, (void (*)(void*, size_t))callback);
}


void* arr_find(array* arr, void* data) {
   void* start = arr->data;
   void* end = arr->data + arr->size * arr->element_size;
   return find(start, end, arr->element_size, data);
}


void* arr_find_rng(array* arr, void* start, void* end, void* data) {
   __check_range(arr, start, end);
   return find(start, end, arr->element_size, data);
}


void* arr_find_n(array* arr, void* start, size_t n, void* data) {
   __check_range(arr, start, start + n * arr->element_size);
   return find(start, start + n * arr->element_size, arr->element_size, data);
}


void* arr_find_if(array* arr, int (*predicate)(void*)) {
   void* start = arr->data;
   void* end = arr->data + arr->size * arr->element_size;
   return find_if(start, end, arr->element_size, predicate);
}


void* arr_find_if_rng(array* arr, void* start, void* end, int (*predicate)(void*)) {
   __check_range(arr, start, end);
   return find_if(start, end, arr->element_size, predicate);
}


void* arr_find_if_n(array* arr, void* start, size_t n, int (*predicate)(void*)) {
   __check_range(arr, start, start + n * arr->element_size);
   return find_if(start, start + n * arr->element_size, arr->element_size, predicate);
}


void* arr_find_if_not(array* arr, int (*predicate)(void*)) {
   void* start = arr->data;
   void* end = arr->data + arr->size * arr->element_size;
   return find_if_not(start, end, arr->element_size, predicate);
}


void* arr_find_if_not_rng(array* arr, void* start, void* end, int (*predicate)(void*)) {
   __check_range(arr, start, end);
   return find_if_not(start, end, arr->element_size, predicate);
}


void* arr_find_if_not_n(array* arr, void* start, size_t n, int (*predicate)(void*)) {
   __check_range(arr, start, start + n * arr->element_size);
   return find_if_not(start, start + n * arr->element_size, arr->element_size, predicate);
}


void _arr_destroyer(array* arr) {
   if (arr->destroyer != NULL) {
      arr_for_each(arr, arr->destroyer);
   }
   free(arr->data);
   arr->data = NULL;
   arr->size = 0;
   arr->element_size = 0;
   arr->destroyer = NULL;
}


void arr_free(array* arr) {
   _arr_destroyer(arr);
}

void arr_clear(array* arr) {
   arr->size = 0;
}


void* arr_begin(array* arr) {
   return arr->data;
}


void* arr_end(array* arr) {
   return arr->data + arr->size * arr->element_size;
}


void* arr_front(array* arr) {
   return arr->data;
}


void* arr_back(array* arr) {
   return arr->data + (arr->size - 1) * arr->element_size;
}


void arr_fill_rng(array* arr, void* start, void* end, void* data) {
   __check_range(arr, start, end);
   fill(start, end, arr->element_size, data);
}


void arr_fill(array* arr, void* data) {
   arr_fill_rng(arr, arr->data, arr->data + arr->size * arr->element_size, data);
}

void arr_fill_n(array* arr, void* start, size_t n, void* data) {
   __check_range(arr, start, start + n * arr->element_size);
   fill_n(start, n, arr->element_size, data);
}

/**
 * Supports negative indexing
 * If out of bounds, return the
*/
void* arr_at(array* arr, int idx) {
   if (idx >= 0) {
      // If out of bounds
      assert(idx < arr->size && "Index out of bounds");
      return arr->data + idx * arr->element_size;
   } else {
      // if too much negative
      assert(idx >= -arr->size && "Index out of bounds");
      return arr->data + (arr->size + idx) * arr->element_size;
   }
}



void arr_reverse(array* arr) {
   void* start = arr->data;
   void* end = arr->data + arr->size * arr->element_size;
   reverse(start, end, arr->element_size);
}

void arr_reverse_n(array* arr, void* start, size_t n) {
   __check_range(arr, start, start + n * arr->element_size);
   reverse(start, start + n * arr->element_size, arr->element_size);
}

void arr_reverse_rng(array* arr, void* start, void* end) {
   __check_range(arr, start, end);
   reverse(start, end, arr->element_size);
}


void arr_sort_cmp(array* arr, int (*cmp)(void*, void*)) {
   void* start = arr->data;
   void* end = arr->data + arr->size * arr->element_size;
   sort(start, end, arr->element_size, cmp);
}

void arr_sort(array* arr) {
   arr_sort_cmp(arr, int_cmp);
}

void arr_sort_n_cmp(array* arr, void* start, size_t n, int (*cmp)(void*, void*)) {
   __check_range(arr, start, start + n * arr->element_size);
   sort(start, start + n * arr->element_size, arr->element_size, cmp);
}

void arr_sort_n(array* arr, void* start, size_t n) {
   arr_sort_n_cmp(arr, start, n, int_cmp);
}

void arr_sort_rng_cmp(array* arr, void* start, void* end, int (*cmp)(void*, void*)) {
   __check_range(arr, start, end);
   sort(start, end, arr->element_size, cmp);
}

void arr_sort_rng(array* arr, void* start, void* end) {
   arr_sort_rng_cmp(arr, start, end, int_cmp);
}
