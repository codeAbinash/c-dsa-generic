#include "../../Data Structures/Vector/vector.h"
#include "../../Data Structures/Vector/vector.c" // TODO: Remove this line
#include "stdio.h"

struct person {
   char* name;
   int age;
};


void print_person(void* data) {
   struct person* p = (struct person*)data;
   printf("Name: %s, Age: %d\n", p->name, p->age);
}


void destroyer(void* data) {
   struct person* p = (struct person*)data;
   printf("Destroyed %s", p->name);
   free(p->name);
}


int main() {
   vector v = vec_init_with_destroyer(2, sizeof(struct person), destroyer);
   struct person p1;
   struct person p2;


   p1.name = (char*)malloc(10);
   strcpy(p1.name, "Abinash");
   p1.age = 20;


   p2.name = (char*)malloc(10);
   strcpy(p2.name, "Tukai");
   p2.age = 35;

   vec_push_back(&v, &p1);
   vec_push_back(&v, &p2);

   vec_for_each(&v, print_person);

   printf("\n\n");
   vec_pop_back(&v);
   printf("\n\n");
   printf("\nAfter pop_back\n");
   printf("\n\n\n");
   vec_for_each(&v, print_person);


   vec_free(&v);

   return 0;
}
