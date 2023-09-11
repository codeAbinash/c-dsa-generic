#include "stddef.h"
#include "string.h"

void selection_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*)) {
   void* i = start;
   while (i < end) {
      void* j = i + element_size;
      void* min = i;
      while (j < end) {
         if (cmp(j, min) < 0) {
            min = j;
         }
         j += element_size;
      }
      if (min != i) {
         void* tmp = malloc(element_size);
         memcpy(tmp, i, element_size);
         memcpy(i, min, element_size);
         memcpy(min, tmp, element_size);
         free(tmp);
      }
      i += element_size;
   }
}

void quick_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*)) {
   size_t total_size = end - start;
   size_t n = total_size / element_size;

   if (n <= 1) {
      return;
   }

   void* pivot = start + (n / 2) * element_size;
   void* left = start;
   void* right = end - element_size;

   while (left <= right) {
      while (cmp(left, pivot) < 0) {
         left += element_size;
      }
      while (cmp(right, pivot) > 0) {
         right -= element_size;
      }
      if (left <= right) {
         swap(left, right, element_size);
         left += element_size;
         right -= element_size;
      }
   }

   quick_sort(start, right + element_size, element_size, cmp);
   quick_sort(left, end, element_size, cmp);
}

void merge_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*)) {
   size_t total_size = end - start;
   size_t n = total_size / element_size;

   if (n <= 1) {
      return;
   }

   void* mid = start + (n / 2) * element_size;

   merge_sort(start, mid, element_size, cmp);
   merge_sort(mid, end, element_size, cmp);

   void* temp = malloc(total_size);
   void* left = start;
   void* right = mid;
   void* ptr = temp;

   while (left < mid && right < end) {
      if (cmp(left, right) < 0) {
         memcpy(ptr, left, element_size);
         left += element_size;
      } else {
         memcpy(ptr, right, element_size);
         right += element_size;
      }
      ptr += element_size;
   }

   while (left < mid) {
      memcpy(ptr, left, element_size);
      left += element_size;
      ptr += element_size;
   }

   while (right < end) {
      memcpy(ptr, right, element_size);
      right += element_size;
      ptr += element_size;
   }

   memcpy(start, temp, total_size);
   free(temp);
}

void insertion_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*)) {
   void* i = start + element_size;
   while (i < end) {
      void* j = i;
      while (j > start && cmp(j, j - element_size) < 0) {
         swap(j, j - element_size, element_size);
         j -= element_size;
      }
      i += element_size;
   }
}

void _heap_ify(void* start, size_t size, int i, size_t element_size, int (*cmp)(void*, void*)) {
   int largest = i;
   int l = 2 * i + 1;
   int r = 2 * i + 2;

   if (l < size && cmp(start + l * element_size, start + largest * element_size) > 0)
      largest = l;

   if (r < size && cmp(start + r * element_size, start + largest * element_size) > 0)
      largest = r;

   if (largest != i) {
      swap(start + i * element_size, start + largest * element_size, element_size);
      _heap_ify(start, size, largest, element_size, cmp);
   }
}

void heap_sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*)) {
   // Start by heapifying the array
   size_t size = (end - start) / element_size;
   for (int i = size / 2 - 1; i >= 0; i--) {
      _heap_ify(start, size, i, element_size, cmp);
   }
   // Now extract the elements one by one from the heap
   for (int i = size - 1; i >= 0; i--) {
      swap(start, start + i * element_size, element_size);
      _heap_ify(start, i, 0, element_size, cmp);
   }
}

int int_cmp(void* a, void* b) {
   return *(int*)a - *(int*)b;
}

void sort(void* start, void* end, size_t element_size, int (*cmp)(void*, void*)) {
   // Use the best sorting algorithm depending on the size of the array and the element size
   size_t total_size = end - start;
   size_t n = total_size / element_size;
   // qsort(start, n, element_size, int_cmp);


   if (element_size <= 8) {
      if (n <= 50) {
         insertion_sort(start, end, element_size, cmp);
      } else if (n <= 100) {
         selection_sort(start, end, element_size, cmp);
      } else {
         quick_sort(start, end, element_size, cmp);
      }
   } else {
      if (n <= 100) {
         insertion_sort(start, end, element_size, cmp);
      } else {
         heap_sort(start, end, element_size, cmp);
      }
   }
}
