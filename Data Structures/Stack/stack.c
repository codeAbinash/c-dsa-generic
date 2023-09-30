/**
 * Library for Stack data structure
 * Author: Abinash Karmakar
 * 2023-09-30
*/

#include "./stack.h"
#include "../Vector/vector.h"
#include "../Vector/vector.c" // TODO: Remove this when the library is complete

/**
 * @brief Initializes a stack with a destroyer function
 * @param element_size Size of each element in the stack
 * @param destroyer Function to destroy each element in the stack
 * @return stack
*/
stack stk_init_with_destroyer(size_t element_size, void (*destroyer)(void*)) {
  stack stk;
  stk.data = vec_init_with_destroyer(0, element_size, destroyer);
  return stk;
}

/**
 * @brief Initializes a stack
 * @param element_size Size of each element in the stack
 * @return stack
*/
stack stk_init(size_t element_size) {
  stack stk;
  stk.data = vec_init(0, element_size);
  return stk;
}

/**
 * @brief Checks if the stack is empty
 * @param stk Stack to check
 * @return 1 if empty, 0 otherwise
*/
int stk_empty(stack* stk) {
  return vec_empty(&stk->data);
}


/**
 * @brief Get the size of the stack
 * @param stk Stack to check
 * @return size of the stack
*/
size_t stk_size(stack* stk) {
  return vec_size(&stk->data);
}

/**
 * @brief Get the top element of the stack
 * @param stk Stack to check
 * @return pointer to the top element of the stack
*/
void* stk_top(stack* stk) {
  return vec_back(&stk->data);
}

/**
 * @brief Push an element to the stack
 * @param stk Stack to push to
 * @param data Pointer to the data to push
 *
*/
void stk_push(stack* stk, void* data) {
  vec_push_back(&stk->data, data);
}

/**
 * @brief Pop an element from the stack
 * @param stk Stack to pop from
*/
void stk_pop(stack* stk) {
  vec_pop_back(&stk->data);
}
