#include "stdio.h"
#include "../../Data Structures/Linked List/linked_list.h"
#include "../../Data Structures/Linked List/linked_list.c" // TODO: Remove this

typedef struct Complex {
   int real, imaginary;
} Complex;

void printComplexNode(ll_node* node) {
   Complex* c = (Complex*)node->data;
   printf("%d + %di\n", c->real, c->imaginary);
}

int main() {
   linked_list list = ll_init(sizeof(Complex));
   // Can store any data type

   Complex c1 = { 1, 2 };
   Complex c2 = { 3, 4 };
   Complex c3 = { 5, 6 };

   ll_push_back(&list, &c1);
   ll_push_back(&list, &c2);
   ll_push_back(&list, &c3);

   printf("Linked List : \n");
   // ll_for_each calls the function for each node
   ll_for_each(&list, printComplexNode);

   ll_reverse(&list); // Reverses the linked list

   printf("\n After Reversing : \n");
   ll_for_each(&list, printComplexNode);

   printf("\nSize: %ld\n", list.size);

   ll_free(&list);
   return 0;
}
