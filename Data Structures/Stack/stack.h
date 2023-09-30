#ifndef c_dsa_generic_stack_h
#define c_dsa_generic_stack_h

#include "../Vector/vector.h"

typedef struct stack {
  vector data;
} stack;

stack stk_init_with_destroyer(size_t element_size, void (*destroyer)(void*));
stack stk_init(size_t element_size);
int stk_empty(stack* stk);
size_t stk_size(stack* stk);
void* stk_top(stack* stk);
void stk_push(stack* stk, void* data);
void stk_pop(stack* stk);

#endif
