// #include "../../c_dsa.h"
#include "../../c_dsa.c" // TODO: Remove this
typedef struct {
   char name[20];
   int age;
} person;

void print_person(void* p) {
   printf("Name: %s, Age: %d\n", ((person*)p)->name, ((person*)p)->age);
}

int compare_person(void* p, void* q) {
   person* p1 = (person*)p;
   person* p2 = (person*)q;

   if (p1->age > p2->age) {
      return 1;
   } else if (p1->age < p2->age) {
      return -1;
   } else {
      return 0;
   }
}

int sort_name_cmp(void* p, void* q) {
   person* p1 = (person*)p;
   person* p2 = (person*)q;
   return strcmp(p1->name, p2->name);
}

int main() {
   array arr = arr_init(10, sizeof(person));
   person p[10] = {
      {"John", 2},
      { "Mary", 300 },
      { "Peter", 32},
      { "Paul", 5 },
      { "Lucy", -609 },
      { "Mark", 7 },
      { "Luke", -8 },
      { "James", 12 },
      { "Jude", 10 },
      { "Matthew", 2},
   };

   person* p1 = (person*)arr.data;

   for (int i = 0; i < 10; i++) {
      p1[i] = p[i];
   }

   printf("Before sorting:\n");
   arr_for_each(&arr, print_person);

   // After sorting by age
   arr_sort_cmp(&arr, compare_person);

   printf("\nAfter sorting by age:\n");
   arr_for_each(&arr, print_person);

   // After sorting by name
   printf("\nAfter sorting by Name:\n");
   arr_sort_cmp(&arr, sort_name_cmp);
   arr_for_each(&arr, print_person);

   arr_free(&arr);

   return 0;
}
