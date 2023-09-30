#include "stdio.h"
#include "../../Data Structures/Stack/stack.h"
#include "../../Data Structures/Stack/stack.c" // TODO: Remove this when the library is complete

int main() {
  int arr[] = { 1, 2, 3, 4, 5 };
  stack s = stk_init(sizeof(int));
  stk_push(&s, arr + 4);
  stk_push(&s, arr + 3);
  stk_push(&s, arr + 2);


  printf("Top of stack: %d\n", *(int*)stk_top(&s));
  printf("Size of stack: %ld\n", stk_size(&s));

  stk_pop(&s);

  printf("Top of stack: %d\n", *(int*)stk_top(&s));
  printf("Size of stack: %ld\n", stk_size(&s));


}
