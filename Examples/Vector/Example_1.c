#include "../../Data Structures/Vector/vector.h"
#include "../../Data Structures/Vector/vector.c" // TODO: Remove this line

void log_int(void* data) {
   printf("%d ", *(int*)data);
}

int main() {
   vector v = vec_init(5, sizeof(int));
   int num = 7;
   int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

   vec_assign_rng(&v, arr, arr + 10);

   vec_push_back(&v, &num);

   vec_sort_rng(&v, vec_begin(&v), vec_end(&v));
   // Or simply vec_sort(&v) can be used

   // Find `num` in the vector
   int* ptr = vec_find(&v, &num);

   if (ptr != vec_end(&v))
      printf("Found %d\n", *ptr);
   else
      printf("Not found\n");

   vec_for_each(&v, log_int);

   printf("\nIterator : ");
   for (int* it = vec_begin(&v); it != vec_end(&v); it++)
      printf("%d ", *it);

   return 0;
}
