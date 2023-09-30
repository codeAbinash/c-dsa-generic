/**
 * Library for a vector data structure.
 * Author : Abinash Karmakar
 * 2023-09-01 MIT License Version: 1.0
*/

#include "malloc.h"
#include "vector.h"
#include "assert.h"
#include "../../Algorithms/algorithms.h"
#include "../../Algorithms/algorithms.c" // TODO: Remove this




/**
 * @brief Factory function for creating a vector.
 * @param size The initial size of the vector.
 * @param element_size The size of each element in the vector.
 * @param destroyer The function that will be called when elements are removed from the vector.
 * @return A vector with the given size, element size and destroyer.
 * @warning It is the responsibility of the user to if the vector allocates memory, to free the memory.
 * Time complexity: O(1)
*/
vector vec_init_with_destroyer(size_t size, size_t element_size, void (*destroyer)(void*)) {
   assert(size >= 0 && "Size must be non negative");
   assert(element_size > 0 && "Element size must be positive");
   vector vec; // Creating a vector.
   vec.size = 0; // Setting the size to 0
   vec.element_size = element_size;
   vec.capacity = size;
   if (size > 0)
      vec.data = malloc(size * element_size);
   else
      vec.data = NULL;
   vec.destroyer = destroyer;
   return vec;
}


/**
 * @brief Factory function for creating a vector.
 * @param size The initial size of the vector.
 * @param element_size The size of each element in the vector.
 * @return A vector with the given size and element size.
 * @note The destroyer is set to NULL.
 * Time complexity: O(1)
*/
vector vec_init(size_t size, size_t element_size) {
   return vec_init_with_destroyer(size, element_size, NULL);
}


/**
 * @brief Function to get the capacity of the vector.
 * @param vec The vector.
 * @return The capacity of the vector.
 * Time complexity: O(1)
*/
size_t vec_capacity(vector* vec) {
   return vec->capacity;
}


/**
 * @brief Function to get the size of the vector.
 * @param vec The vector.
 * @return The size of the vector.
 * Time complexity: O(1)
*/
size_t vec_size(vector* vec) {
   return vec->size;
}


/**
 * @brief Function to get the maximum size or the capacity of the vector.
 * @param vec The vector.
 * @return The maximum size or the capacity of the vector.
 * Time complexity: O(1)
*/
size_t vec_max_size(vector* vec) {
   return vec->capacity;
}


/**
 * @brief Function to get the size of each element in the vector.
 * @param vec The vector.
 * @return The size of each element in the vector.
 * Time complexity: O(1)
*/
size_t vec_element_size(vector* vec) {
   return vec->element_size;
}


/**
 * @brief Function to check if the vector is empty.
 * @param vec The vector.
 * @return 1 if the vector is empty, 0 otherwise.
 * Time complexity: O(1)
*/
int vec_empty(vector* vec) {
   return vec->size == 0;
}


/**
 * @brief Function to get void pointer to the first element of the vector.
 * @param vec The vector.
 * @return A void pointer to the first element of the vector.
 * Time complexity: O(1)
 * @note This function is the same as vec_front.
*/
void* vec_begin(vector* vec) {
   return vec->data;
}


/**
 * @brief Function to get void pointer to the last element of the vector.
 * @param vec The vector.
 * @return A void pointer to the last element of the vector.
 * Time complexity: O(1)
 * @note This function is the same as vec_end.
*/
void* vec_end(vector* vec) {
   return vec->data + vec->size * vec->element_size;
}


/**
 * @brief Function to get void pointer to the first element of the vector.
 * @param vec The vector.
 * @return A void pointer to the first element of the vector.
 * Time complexity: O(1)
 * @note This function is the same as vec_begin.
*/
void* vec_front(vector* vec) {
   return vec->data;
}


/**
 * @brief Function to get void pointer to the last element of the vector.
 * @param vec The vector.
 * @return A void pointer to the last element of the vector.
 * Time complexity: O(1)
*/
void* vec_back(vector* vec) {
   return vec->data + (vec->size - 1) * vec->element_size;
}


/**
 * @brief Function to assert that the range [start, end) is valid for the vector.
 * @param vec The vector.
 * @param start The start pointer of the range.
 * @param end The end pointer of the range.
 * @warning The range must be valid for the vector.
 * Time complexity: O(1)
 * @note This function is used internally by the library.
*/
void __check_range(vector* vec, void* start, void* end) {
   assert(start >= vec->data && "Start pointer out of bounds");
   assert(end <= vec->data + vec->size * vec->element_size && "End pointer out of bounds");
   assert(start <= end && "Start pointer must be less than or equal to end pointer");
   assert((end - start) % vec->element_size == 0 && "Invalid range");
}



/**
 * @brief Function to call a callback function for each element in the vector with the index.
 * @param vec The vector.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_for_each_idx(vector* vec, void (*callback)(void*, size_t)) {
   void* start = vec->data;
   void* end = vec->data + vec->size * vec->element_size;
   for_each_idx(start, end, vec->element_size, callback);
}


/**
 * @brief Function to call a callback function for each element in the vector.
 * @param vec The vector.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_for_each(vector* vec, void (*callback)(void*)) {
   vec_for_each_idx(vec, (void (*)(void*, size_t))callback);
}


/**
 * @brief Function to call a callback function for each element starting from `start` in the vector with the index.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_for_each_n_idx(vector* vec, void* start, size_t n, void (*callback)(void*, size_t)) {
   __check_range(vec, start, start + n * vec->element_size);
   for_each_n_idx(start, n, vec->element_size, callback);
}


/**
 * @brief Function to call a callback function for each element starting from `start` in the vector.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_for_each_n(vector* vec, void* start, size_t n, void (*callback)(void*)) {
   vec_for_each_n_idx(vec, start, n, (void (*)(void*, size_t))callback);
}


/**
 * @brief Function to call a callback function for each element in the range [start, end) in the vector with the index.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_for_each_rng_idx(vector* vec, void* start, void* end, void (*callback)(void*, size_t)) {
   __check_range(vec, start, end);
   for_each_rng_idx(start, end, vec->element_size, callback);
}


/**
 * @brief Function to call a callback function for each element in the range [start, end) in the vector.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_for_each_rng(vector* vec, void* start, void* end, void (*callback)(void*)) {
   vec_for_each_rng_idx(vec, start, end, (void (*)(void*, size_t))callback);
}


/**
 * @brief Function to modify each element in the vector with the index by calling a callback function.
 * @param vec The vector.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_map_idx(vector* vec, void (*callback)(void*, size_t)) {
   vec_for_each_idx(vec, callback);
}

/**
 * @brief Function to modify each element in the vector by calling a callback function.
 * @param vec The vector.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_map(vector* vec, void (*callback)(void*)) {
   vec_map_idx(vec, (void (*)(void*, size_t))callback);
}

/**
 * @brief Function to modify each element starting from `start` in the vector with the index by calling a callback function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_map_n_idx(vector* vec, void* start, size_t n, void (*callback)(void*, size_t)) {
   vec_for_each_n_idx(vec, start, n, callback);
}


/**
 * @brief Function to modify each element starting from `start` in the vector by calling a callback function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_map_n(vector* vec, void* start, size_t n, void (*callback)(void*)) {
   vec_map_n_idx(vec, start, n, (void (*)(void*, size_t))callback);
}


/**
 * @brief Function to modify each element in the range [start, end) in the vector with the index by calling a callback function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_map_rng_idx(vector* vec, void* start, void* end, void (*callback)(void*, size_t)) {
   vec_for_each_rng_idx(vec, start, end, callback);
}



/**
 * @brief Function to modify each element in the range [start, end) in the vector by calling a callback function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param callback The callback function.
 * Time complexity: O(n)
*/
void vec_map_rng(vector* vec, void* start, void* end, void (*callback)(void*)) {
   vec_map_rng_idx(vec, start, end, (void (*)(void*, size_t))callback);
}


/**
 * @brief Function to find the first occurrence of a value in the vector.
 * @param vec The vector.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the vector. If not found,
 *         returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find(vector* vec, void* data) {
   return find(vec->data, vec->data + vec->size * vec->element_size, vec->element_size, data);
}


/**
 * @brief Function to find the first occurrence of a value in the range [start, end) in the vector.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the range [start, end) in the vector.
 *         If not found returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_rng(vector* vec, void* start, void* end, void* data) {
   __check_range(vec, start, end);
   return find_rng(start, end, vec->element_size, data);
}


/**
 * @brief Function to find the first occurrence of a value in the range [start, start + n) in the vector.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the range [start, start + n) in the vector.
 *        If not found returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_n(vector* vec, void* start, size_t n, void* data) {
   __check_range(vec, start, start + n * vec->element_size);
   return find_n(start, n, vec->element_size, data);
}



/**
 * @brief Function to find the first occurrence of a value in the vector using a predicate function.
 * @param vec The vector.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the vector. If not found,
 *        returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_if(vector* vec, int (*predicate)(void*)) {
   return find_if(vec->data, vec->data + vec->size * vec->element_size, vec->element_size, predicate);
}


/**
 * @brief Function to find the first occurrence of a value in the range [start, end) in the vector using a predicate function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the range [start, end) in the vector.
 *       If not found returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_if_rng(vector* vec, void* start, void* end, int (*predicate)(void*)) {
   __check_range(vec, start, end);
   return find_if_rng(start, end, vec->element_size, predicate);
}


/**
 * @brief Function to find the first occurrence of a value in the range [start, start + n) in the vector using a predicate function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the range [start, start + n) in the vector.
 *      If not found returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_if_n(vector* vec, void* start, size_t n, int (*predicate)(void*)) {
   __check_range(vec, start, start + n * vec->element_size);
   return find_if_n(start, n, vec->element_size, predicate);
}


/**
 * @brief Function to find the first occurrence of a value in the vector using a predicate function.
 * @param vec The vector.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the vector. If not found,
 *       returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_if_not(vector* vec, int (*predicate)(void*)) {
   return find_if_not(vec->data, vec->data + vec->size * vec->element_size, vec->element_size, predicate);
}


/**
 * @brief Function to find the first occurrence of a value in the range [start, end) in the vector using a predicate function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the range [start, end) in the vector.
 *     If not found returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_if_not_rng(vector* vec, void* start, void* end, int (*predicate)(void*)) {
   __check_range(vec, start, end);
   return find_if_not_rng(start, end, vec->element_size, predicate);
}


/**
 * @brief Function to find the first occurrence of a value in the range [start, start + n) in the vector using a predicate function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param data The data to find.
 * @return A void pointer to the first occurrence of the value in the range [start, start + n) in the vector.
 *   If not found returns a pointer to the end of the vector.
 * Time complexity: O(n)
*/
void* vec_find_if_not_n(vector* vec, void* start, size_t n, int (*predicate)(void*)) {
   __check_range(vec, start, start + n * vec->element_size);
   return find_if_not_n(start, n, vec->element_size, predicate);
}


/**
 * @brief Function to reverse the vector.
 * @param vec The vector.
 * Time complexity: O(n)
*/
void vec_reverse(vector* vec) {
   void* start = vec->data;
   void* end = vec->data + vec->size * vec->element_size;
   reverse(start, end, vec->element_size);
}


/**
 * @brief Function to reverse the vector starting from `start` to `start + n`.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * Time complexity: O(n)
*/
void vec_reverse_n(vector* vec, void* start, size_t n) {
   __check_range(vec, start, start + n * vec->element_size);
   reverse(start, start + n * vec->element_size, vec->element_size);
}


/**
 * @brief Function to reverse the vector in the range [start, end).
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
*/
void vec_reverse_rng(vector* vec, void* start, void* end) {
   __check_range(vec, start, end);
   reverse(start, end, vec->element_size);
}


/**
 * @brief Function to sort the vector using a comparator function.
 * @param vec The vector.
 * @param cmp The comparator function.
 * Time complexity: O(n)
 * @note The comparator function must return 1 to swap the elements, 0 otherwise.
*/
void vec_sort_cmp(vector* vec, int (*cmp)(void*, void*)) {
   void* start = vec->data;
   void* end = vec->data + vec->size * vec->element_size;
   sort(start, end, vec->element_size, cmp);
}


/**
 * @brief Function to sort the vector
 * @param vec The vector.
 * Time complexity: O(n log n)
*/
void vec_sort(vector* vec) {
   vec_sort_cmp(vec, int_cmp);
}



/**
 * @brief Function to sort the vector starting from `start` to `start + n` using a comparator function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param cmp The comparator function.
 * Time complexity: O(n log n)
*/
void vec_sort_n_cmp(vector* vec, void* start, size_t n, int (*cmp)(void*, void*)) {
   __check_range(vec, start, start + n * vec->element_size);
   sort(start, start + n * vec->element_size, vec->element_size, cmp);
}



/**
 * @brief Function to sort the vector starting from `start` to `start + n`.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * Time complexity: O(n log n)
*/
void vec_sort_n(vector* vec, void* start, size_t n) {
   vec_sort_n_cmp(vec, start, n, int_cmp);
}


/**
 * @brief Function to sort the vector in the range [start, end) using a comparator function.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param cmp The comparator function.
 * Time complexity: O(n log n)
*/
void vec_sort_rng_cmp(vector* vec, void* start, void* end, int (*cmp)(void*, void*)) {
   __check_range(vec, start, end);
   sort(start, end, vec->element_size, cmp);
}


/**
 * @brief Function to sort the vector in the range [start, end).
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n log n)
*/
void vec_sort_rng(vector* vec, void* start, void* end) {
   vec_sort_rng_cmp(vec, start, end, int_cmp);
}


/**
 * @brief Function to fill the vector with a value in the range [start, end).
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * @param data The data to fill.
 * Time complexity: O(n)
*/
void vec_fill_rng(vector* vec, void* start, void* end, void* data) {
   __check_range(vec, start, end);
   fill(start, end, vec->element_size, data);
}


/**
 * @brief Function to fill the vector with a value.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param data The data to fill.
 * Time complexity: O(n)
*/
void vec_fill(vector* vec, void* data) {
   vec_fill_rng(vec, vec->data, vec->data + vec->size * vec->element_size, data);
}


/**
 * @brief Function to fill the vector with a value starting from `start` to `start + n`.
 * @param vec The vector.
 * @param start The start pointer.
 * @param n The number of elements to iterate.
 * @param data The data to fill.
 * Time complexity: O(n)
*/
void vec_fill_n(vector* vec, void* start, size_t n, void* data) {
   __check_range(vec, start, start + n * vec->element_size);
   vec_fill_rng(vec, start, start + n * vec->element_size, data);
}


/**
 * @brief Function to get the void pointer to the element at the given index.
 * @param vec The vector.
 * @param index The index of the element.
 * @return A void pointer to the element at the given index.
 * Time complexity: O(1)
 * @note If the index is negative, then the index is calculated from the end of the vector.
 * @note If the index is out of bounds, then the program is aborted.
*/
void* vec_at(vector* vec, int index) {
   if (index >= 0) {
      // If out of bounds
      assert(index < vec->size && "Index out of bounds");
      return vec->data + index * vec->element_size;
   } else {
      // if too much negative
      assert(index >= -vec->size && "Index out of bounds");
      return vec->data + (vec->size + index) * vec->element_size;
   }
}


/**
 * @brief Function to destroy the vector in the range [start, end).
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
 * @note This function is used internally by the library.
*/
void __vec_destroy_rng(vector* vec, void* start, void* end) {
   // Destroying in the range [start, end) of the vector. but not freeing the vector.
   void* pos = start;
   if (vec->destroyer != NULL) {
      while (pos != end) {
         vec->destroyer(pos);
         pos += vec->element_size;
      }
   }
}


/**
 * @brief Function to destroy each item in the vector, but not freeing the vector.
 * @param vec The vector.
 * Time complexity: O(n)
 * @note This function is used internally by the library.
 * @warning It is the responsibility of the user to if the vector allocates memory, to free the memory.
*/
void __vec_destroy_each_item(vector* vec) {
   // Destroying each item in the vector, but not freeing the vector.
   void* start = vec->data;
   void* end = vec->data + vec->size * vec->element_size;
   __vec_destroy_rng(vec, start, end);
}


/**
 * @brief Function to destroy the vector fully.
 * @param vec The vector.
 * Time complexity: O(n)
*/
void __vec_destroyer(vector* vec) {
   __vec_destroy_each_item(vec);
   free(vec->data);
   vec->data = NULL;
   vec->size = 0;
   vec->capacity = 0;
   vec->element_size = 0;
   vec->destroyer = NULL;
}


/**
 * @brief Function to destroy the vector fully.
 * @param vec The vector.
 * Time complexity: O(n)
 * @note similar to __vec_destroyer
*/
void vec_free(vector* vec) {
   __vec_destroyer(vec);
}


/**
 * @brief Function to delete all the elements in the vector, but not freeing the vector.
 * @param vec The vector.
 * Time complexity: O(n)
*/
void vec_clear(vector* vec) {
   // Destroying each item in the vector, but not freeing the vector.
   __vec_destroy_each_item(vec);
   vec->size = 0;
}


/**
 * @brief Function to reallocate the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
 * @note This function is used internally by the library.
*/
void __force_reserve_to(vector* vec, size_t size) {
   vec->data = realloc(vec->data, size * vec->element_size);
   vec->capacity = size;
}


/**
 * @brief Function to reallocate and resize the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
 * @note This function is used internally by the library.
*/
void __force_resize_to(vector* vec, size_t size) {
   if (size == 0) { vec_clear(vec);return; }
   __force_reserve_to(vec, size);
   vec->size = size;
}


/**
 * @brief Function to resize the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
*/
void vec_resize(vector* vec, size_t size) {
   assert(size >= 0 && "Size must be non negative");
   // If the size is equal to the current size, then do nothing.
   if (size == vec->size) return;
   if (size > vec->capacity) {
      __force_resize_to(vec, size);
   } else if (size < vec->size) {
      // if `size` is less than the current size, then the last elements are destroyed.
      void* start = vec->data + size * vec->element_size;
      void* end = vec->data + vec->size * vec->element_size;
      __vec_destroy_rng(vec, start, end);
   }
   vec->size = size;
}


/**
 * @brief Function to reserve the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
*/
void vec_reserve(vector* vec, size_t size) {
   assert(size >= 0 && "Size must be non negative");
   size_t capacity = vec->capacity;
   // If the size is less than the current capacity, then do nothing.
   if (size <= capacity) return;
   // If the size is greater than the current capacity, then resize the vector.
   __force_reserve_to(vec, size);
}


/**
 * @brief Function to shrink the vector to the given size.
 * @param vec The vector.
 * @param size The new size of the vector.
 * Time complexity: O(n)
*/
void vec_shrink_to_fit(vector* vec) {
   __force_reserve_to(vec, vec->size);
}



/**
 * @brief Function to remove the last element from the vector.
 * @param vec The vector.
 * Time complexity: O(1)
*/
void vec_pop_back(vector* vec) {
   // Check if the vector is empty.
   assert(vec->size > 0 && "Vector is empty");
   // Destroying the last element.
   void* pos = vec->data + (vec->size - 1) * vec->element_size;
   if (vec->destroyer != NULL) {
      vec->destroyer(pos);
   }
   vec->size--;
}


/**
 * @brief Function to insert the data to the end of the vector.
 * @param vec The vector.
 * @param data The data to insert.
 * Time complexity: O(1)
 * @note This function is used internally by the library.
*/
void __valid_pos(vector* vec, void* pos) {
   // Check if the position is valid.
   void* end = vec->data + vec->size * vec->element_size;
   assert(pos >= vec->data && "Position pointer out of bounds, before start");
   assert(pos < end && "Position pointer out of bounds, after end");
}


/**
 * @brief Function to check if the range is valid.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(1)
 * @note This function is used internally by the library.
*/
void __check_erase_bounds(vector* vec, void* start, void* end) {
   // Check if the position is valid.
   __valid_pos(vec, start);
   __valid_pos(vec, end);
   // Check if the range is valid.
   if (start == end) return;
   assert(start <= end && "Start pointer must be less than or equal to end pointer");
   // Must be multiple of element size.
   assert((end - start) % vec->element_size == 0 && "Invalid range");
}


/**
 * @brief Function to erase the elements in the range [start, end) in the vector.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
*/
void vec_erase_rng(vector* vec, void* start, void* end) {
   // Check if the range is valid.
   __check_erase_bounds(vec, start, end);
   // Destroying the elements in the range.
   __vec_destroy_rng(vec, start, end);
   // Moving the elements after the range to the left.
   size_t size = vec->data + vec->size * vec->element_size - end;
   memmove(start, end, size);
   vec->size -= (end - start) / vec->element_size;
}



/**
 * @brief Function to erase the element in the vector at the given position.
 * @param vec The vector.
 * @param pos The position pointer.
 * Time complexity: O(n)
*/
void vec_erase(vector* vec, void* pos) {
   // Check if the position is valid.
   __valid_pos(vec, pos);
   void* end = vec->data + vec->size * vec->element_size;
   // Destroying the element at the position.
   if (vec->destroyer != NULL) {
      vec->destroyer(pos);
   }
   // Moving the elements after the position to the left.
   size_t size = end - pos - vec->element_size;
   memmove(pos, pos + vec->element_size, size);
   vec->size--;
}



/**
 * @brief Function to insert the data to the given position in the vector.
 * @param vec The vector.
 * @param pos The position pointer.
 * @param data The data to insert.
 * Time complexity: O(n)
*/
void vec_insert(vector* vec, void* pos, void* data) {
   // If the position is out of bound of [start, end) of the vector, then do nothing.
   // Here end is the address of the last element of the allocated memory.
   void* start = vec->data;
   void* capacityEnd = vec->data + vec->capacity * vec->element_size;
   void* end = vec->data + vec->size * vec->element_size;

   assert(pos >= start && "Position pointer out of bounds, before start");
   assert(pos <= capacityEnd && "Position pointer out of bounds, after end");

   if (pos == end) {
      vec_push_back(vec, data);
      return;
   }

   if (pos > end) {
      // Move the elements after the end to the right.
      size_t size = pos - end;
      // Copying the data to the position.
      memcpy(pos, data, vec->element_size);
      vec->size += (pos - end) / vec->element_size + 1;
   } else {
      // Move the elements after the end to the right.
      size_t size = end - pos;
      memmove(pos + vec->element_size, pos, size);
      // Copying the data to the position.
      memcpy(pos, data, vec->element_size);
      vec->size++;
   }
}


/**
 * @brief Function to insert a range of data to the given position in the vector.
 * @param vec The vector.
 * @param pos The position pointer.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
*/
void vec_insert_rng(vector* vec, void* pos, void* start, void* end) {
   // If the position is out of bound of [start, end) of the vector, then do nothing.
   // Here end is the address of the last element of the allocated memory.
   void* capacityEnd = vec->data + vec->capacity * vec->element_size;
   void* vecEnd = vec->data + vec->size * vec->element_size;

   assert(pos >= vec->data && "Position pointer out of bounds, before start");
   assert(pos <= capacityEnd && "Position pointer out of bounds, after end");
   // Check if the range is valid.
   assert(start <= end && "Start pointer must be less than or equal to end pointer");
   assert((end - start) % vec->element_size == 0 && "Invalid range");
   assert(end - start <= capacityEnd - vecEnd && "Not enough space in vector");

   if (pos >= vecEnd) {
      // Move the elements after the end to the right.
      size_t size = pos - vecEnd + (end - start);
      // Copying the data to the position.
      memcpy(pos, start, end - start);
      vec->size += (pos - vecEnd) / vec->element_size + (end - start) / vec->element_size;
   } else {
      // Move the elements after the end to the right.
      size_t size = vecEnd - pos;
      memmove(pos + (end - start), pos, size);
      // Copying the data to the position.
      memcpy(pos, start, end - start);
      vec->size += (end - start) / vec->element_size;
   }
}



/**
 * @brief Function to assign the vector to the given size and fill it with the given data.
 * @param vec The vector.
 * @param n The new size of the vector.
 * @param data The data to fill.
 * Time complexity: O(n)
*/
void vec_assign(vector* vec, size_t n, void* data) {
   assert(n >= 0 && "n must be non negative");
   // Destroying each item in the vector, but not freeing the vector.
   __vec_destroy_each_item(vec);
   // If the size is greater than the current capacity, then resize the vector.
   if (n > vec->capacity) {
      __force_resize_to(vec, n);
   }
   // Copying the data to the vector.
   void* dest = vec->data;
   vec->size = n;
   for (size_t i = 0; i < n; i++) {
      memcpy(dest, data, vec->element_size);
      dest += vec->element_size;
   }
}


/**
 * @brief Function to assign the vector to the given range and fill it with the given data.
 * @param vec The vector.
 * @param start The start pointer.
 * @param end The end pointer.
 * Time complexity: O(n)
*/
void vec_assign_rng(vector* vec, void* start, void* end) {
   size_t element_size = vec->element_size;
   size_t size = (end - start) / element_size;
   assert(size >= 0 && "Size must be non negative");
   // Destroying each item in the vector, but not freeing the vector.
   __vec_destroy_each_item(vec);
   // If the size is greater than the current capacity, then resize the vector.
   if (size > vec->capacity) {
      __force_resize_to(vec, size);
   }
   // Copying the data to the vector.
   void* dest = vec->data;
   vec->size = size;
   for (size_t i = 0; i < size; i++) {
      memcpy(dest, start, element_size);
      dest += element_size;
      start += element_size;
   }
}

/**
 * @brief Function to make the vector size to double the current size.
 * @param vec The vector.
 * Time complexity: O(n)
 * @note This function is used internally by the library.
*/
void __vec_double_if_full(vector* vec) {
   // If the vector is full, double the size of the vector.
   if (vec->size == vec->capacity) {
      // If the size is 0, then double the size to 1.
      if (vec->size == 0)
         __force_reserve_to(vec, 1);
      else
         __force_reserve_to(vec, vec->capacity * 2);
   }
}

/**
 * @brief Function to push the data to the end of the vector.
 * @param vec The vector.
 * @param data The data to push.
 * Time complexity: O(1)
 * @note If the vector is full, then the vector size is doubled.
*/
void vec_push_back(vector* vec, void* data) {
   // Check if the vector is full. If full, double the size of the vector.
   __vec_double_if_full(vec);
   // Copying the data to the end of the vector.
   void* dest = vec->data + vec->size * vec->element_size;
   vec->size++;
   memcpy(dest, data, vec->element_size);
}

// End of 'Data Structures/Vector/Vector.c'
