#include "stdio.h"
#include "../../Linked List/linked_list.h"
#include "../../Linked List/linked_list.c"

typedef struct Array {
   int* data;
   size_t size;
} Array;

void print_array(ll_node* node) {
   Array* a = (Array*)node->data;
   for (int i = 0; i < a->size; i++) {
      printf("%d ", a->data[i]);
   }
   printf("\n");
}

// Using a destructor to free the allocated memory by the user
void destroyer(ll_node* node) {
   Array* a = (Array*)node->data;
   free(a->data);
   ll_node_free(node);
   printf("Destroyed\n");
}

int main() {
   Array a1;
   a1.data = (int*)malloc(sizeof(int) * 2);
   a1.data[0] = 1, a1.data[1] = 2, a1.data[2] = 3;
   a1.size = 3;

   Array a2; // Dynamically allocate the array
   a2.data = (int*)malloc(sizeof(int) * 2);
   a2.data[0] = 4, a2.data[1] = 5, a2.data[2] = 6;
   a2.size = 3;

   linked_list list = ll_init_with_destroyer(sizeof(Array), destroyer);

   ll_push_back(&list, &a1);
   ll_push_back(&list, &a2);

   ll_for_each(&list, print_array);

   ll_pop_back(&list); // This will call the user defined destroyer
   ll_pop_back(&list); // This will call the user defined destroyer
}