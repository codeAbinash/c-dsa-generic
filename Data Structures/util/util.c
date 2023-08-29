#include "util.h"
#include "stddef.h"
#include "string.h"
#include "stdlib.h"

int int_cmp(void* a, void* b);


void fill(void* start, void* end, size_t element_size, void* value) {
   for (void* ptr = start; ptr < end; ptr += element_size) {
      memcpy(ptr, value, element_size);
   }
}

void fill_n(void* start, size_t n, size_t element_size, void* value) {
   fill(start, start + n * element_size, element_size, value);
}


void for_each_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t)) {
   size_t i = 0;
   for (void* ptr = start; ptr < end; ptr += element_size) {
      callback(ptr, i);
      i++;
   }
}

void for_each(void* start, void* end, size_t element_size, void (*callback)(void*)) {
   for_each_idx(start, end, element_size, (void (*)(void*, size_t))callback);
}

void for_each_n_idx(void* start, size_t n, size_t element_size, void (*callback)(void*, size_t)) {
   for_each_idx(start, start + n * element_size, element_size, callback);
}

void for_each_n(void* start, size_t n, size_t element_size, void (*callback)(void*)) {
   for_each_n_idx(start, n, element_size, (void (*)(void*, size_t))callback);
}

void for_each_rng_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t)) {
   for_each_idx(start, end, element_size, callback);
}

void for_each_rng(void* start, void* end, size_t element_size, void (*callback)(void*)) {
   for_each_rng_idx(start, end, element_size, (void (*)(void*, size_t))callback);
}


void map_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t)) {
   for_each_idx(start, end, element_size, callback);
}

void map(void* start, void* end, size_t element_size, void (*callback)(void*)) {
   map_idx(start, end, element_size, (void (*)(void*, size_t))callback);
}

void map_n_idx(void* start, size_t n, size_t element_size, void (*callback)(void*, size_t)) {
   map_idx(start, start + n * element_size, element_size, callback);
}

void map_n(void* start, size_t n, size_t element_size, void (*callback)(void*)) {
   map_n_idx(start, n, element_size, (void (*)(void*, size_t))callback);
}

void map_rng_idx(void* start, void* end, size_t element_size, void (*callback)(void*, size_t)) {
   map_idx(start, end, element_size, callback);
}

void map_rng(void* start, void* end, size_t element_size, void (*callback)(void*)) {
   map_rng_idx(start, end, element_size, (void (*)(void*, size_t))callback);
}

/**
 * If the value is found, returns a pointer to the value.
 * Otherwise, returns a pointer to the end of the range.
*/
void* find_cmp(void* start, void* end, size_t element_size, void* value, int (*cmp)(void*, void*, size_t)) {
   for (void* ptr = start; ptr < end; ptr += element_size) {
      if (cmp(ptr, value, element_size) == 0) {
         return ptr;
      }
   }
   return end;
}

void* find(void* start, void* end, size_t element_size, void* value) {
   return find_cmp(start, end, element_size, value, (int(*)(void*, void*, size_t))memcmp);
}

void* find_n_cmp(void* start, size_t n, size_t element_size, void* value, int (*cmp)(void*, void*, size_t)) {
   return find_cmp(start, start + n * element_size, element_size, value, cmp);
}

void* find_n(void* start, size_t n, size_t element_size, void* value) {
   return find_n_cmp(start, n, element_size, value, (int(*)(void*, void*, size_t))memcmp);
}

void* find_rng_cmp(void* start, void* end, size_t element_size, void* value, int (*cmp)(void*, void*, size_t)) {
   return find_cmp(start, end, element_size, value, cmp);
}

void* find_rng(void* start, void* end, size_t element_size, void* value) {
   return find_rng_cmp(start, end, element_size, value, (int(*)(void*, void*, size_t)) memcmp);
}

/**
 * If the value is found, returns a pointer to the value.
 * Otherwise, returns a pointer to the end of the range.
*/
void* find_if(void* start, void* end, size_t element_size, int (*predicate)(void*)) {
   for (void* ptr = start; ptr < end; ptr += element_size) {
      if (predicate(ptr)) {
         return ptr;
      }
   }
   return end;
}

void* find_if_n(void* start, size_t n, size_t element_size, int (*predicate)(void*)) {
   return find_if(start, start + n * element_size, element_size, predicate);
}

void* find_if_rng(void* start, void* end, size_t element_size, int (*predicate)(void*)) {
   return find_if(start, end, element_size, predicate);
}

void* find_if_not(void* start, void* end, size_t element_size, int (*predicate)(void*)) {
   for (void* ptr = start; ptr < end; ptr += element_size) {
      if (!predicate(ptr)) {
         return ptr;
      }
   }
   return end;
}

void* find_if_not_n(void* start, size_t n, size_t element_size, int (*predicate)(void*)) {
   return find_if_not(start, start + n * element_size, element_size, predicate);
}

void* find_if_not_rng(void* start, void* end, size_t element_size, int (*predicate)(void*)) {
   return find_if_not(start, end, element_size, predicate);
}

void* reverse(void* start, void* end, size_t element_size) {
   size_t total_size = end - start;
   size_t half_size = total_size / 2;

   byte* left = start;
   byte* right = end - element_size;

   for (size_t i = 0; i < half_size; i += element_size) {
      for (size_t j = 0; j < element_size; j++) {
         byte temp = left[j];
         left[j] = right[j];
         right[j] = temp;
      }
      left += element_size;
      right -= element_size;
   }
   return start;
}

void* reverse_n(void* start, size_t n, size_t element_size) {
   return reverse(start, start + n * element_size, element_size);
}

void* reverse_rng(void* start, void* end, size_t element_size) {
   return reverse(start, end, element_size);
}


void swap(void* a, void* b, size_t element_size) {
   for (size_t i = 0; i < element_size; i++) {
      byte temp = ((byte*)a)[i];
      ((byte*)a)[i] = ((byte*)b)[i];
      ((byte*)b)[i] = temp;
   }
}


