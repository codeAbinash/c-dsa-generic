/*
*  Header file for Singly Linked List of C-DSA-Crafts library
*  Author: Abinash Karmakar
*  https://github.com/codeAbinash/c-dsa-generic
*  2023-08-28, MIT License, Version: 1.0
*/

#ifndef c_dsa_crafts_singly_linked_list_h
#define c_dsa_crafts_singly_linked_list_h

#include "stddef.h"


/**
 * @brief Node of a Singly Linked List
 * @var data: void pointer to the data
 * @var next: pointer to the next node
*/
typedef struct ll_node {
   void* data;
   struct ll_node* next;
} ll_node;


/**
 * @brief Singly Linked List
 * @var length: length of the list
 * @var head: pointer to the head node
 * @var tail: pointer to the tail node
 * @var element_size: size of each element in the list
 * @var destroyer: function pointer to the destroyer function
*/
typedef struct LinkedList {
   size_t length;
   ll_node* head;
   ll_node* tail;
   size_t element_size;
   void (*destroyer)(ll_node*);
} LinkedList;


/**
 * @brief Factory function to create a new Singly Linked List with a destroyer function
 * @param element_size: size of each element in the list
 * @param destroyer: function pointer to the destroyer function
 * @return LinkedList: a new Singly Linked List wrapped in a struct
 * @warning Define a custom destroyer function to free the memory of the pointers
 * It is the responsibility of the caller to free the memory
 * @warning The destroyer function should have the following signature:
 *    The parameter is the pointer to the node that is to be destroyed
 *    The function should free the memory of the pointer(s) that is(are) stored in the data field
 *    Or it may cause memory leak
 * @note Use ll_node_free() to free the memory of a node
 * Time Complexity: O(1)
*/
LinkedList ll_init_with_destroyer(size_t element_size, void (*destroyer)(ll_node*));


/**
 * @brief Factory function to create a new Singly Linked List with default destroyer function
 * @param element_size: size of each element in the list
 * @return LinkedList: a new Singly Linked List wrapped in a struct
 * @note This function will automatically free the memory after deleting a
 *       node using the destructive functions defined in this header file
 * @warning It will not free the memory of the pointer(s) that is(are) stored in the data field
 * Time Complexity: O(1)
*/
LinkedList ll_init(size_t element_size);


/**
 * @brief Function to create a new node
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @return ll_node: pointer to the new node
 * @note The data will be shallow copied
 * Time Complexity: O(1)
*/
ll_node* ll_create_node(LinkedList* list, void* data);


/**
 * @brief Function to get the length of the list
 * @param list: pointer to the list
 * @return size_t: length of the list
 *
 * Time Complexity: O(1)
*/
size_t ll_size(LinkedList* list);


/**
 * @brief Function to free the memory of a node
 * @param node: pointer to the node
 * @warning This function will not free the the pointer(s) that is(are) stored in the data field
 * @note Use a custom destroyer function to free the pointers
 * Time Complexity: O(1)
*/
void ll_node_destroyer(ll_node* node);


/**
 * @brief Same as ll_node_destroyer()
 * @note Calls ll_node_destroyer() internally
 * Time Complexity: O(1)
*/
void ll_node_free(ll_node* node);

/**
 * If the destroyer function is defined, it will be called
 * Otherwise, it will call ll_node_destroyer()
 * @param destroyer: function pointer to the destroyer function
 * @param node: pointer to the node
*/
void _ll_node_destroyer(void (*destroyer)(ll_node*), ll_node* node);


/**
 * @brief Function to free the memory of the list and all the nodes
 * @param list: pointer to the list
 * @warning This function will not free the the pointer(s) that is(are) stored in the data field
 * @note Use a custom destroyer function to free the pointers
 * Time Complexity: O(n)
*/
void ll_destroyer(LinkedList* list);


/**
 * @brief Same as ll_destroyer()
 * @note Calls ll_destroyer() internally
 * Time Complexity: O(n)
*/
void ll_free(LinkedList* list);


/**
 * @brief Calls the callback function for each node in the list
 * @param list: pointer to the list
 * @param callback: function pointer to the callback function
 * @note The callback function should have the following signature:
 *      void callback(ll_node*, size_t)
 *       The first parameter is the pointer to the node
 *       The second parameter is the index of the node
 * Time Complexity: O(n)
*/
void ll_for_each(LinkedList* list, void (*callback)(ll_node*, size_t));


/**
 * @brief Inserts a new node at the end of the list
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @note The data will be shallow copied
 * Time Complexity: O(1)
*/
void ll_push_front(LinkedList* list, void* data);


/**
 * @brief Deletes the first node of the list
 * @param list: pointer to the list
 * @note internally calls ll_node_destroyer() or the custom destroyer function
 * Time Complexity: O(1)
*/
void ll_pop_front(LinkedList* list);


/**
 * @brief Deletes the last node of the list
 * @param list: pointer to the list
 * @note internally calls ll_node_destroyer() or the custom destroyer function
 * Time Complexity: O(n)
*/
void ll_pop_back(LinkedList* list);


/**
 * @brief Inserts a new node at the end of the list
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @note The data will be shallow copied
 * Time Complexity: O(1)
*/
void ll_push_back(LinkedList* list, void* data);


/**
 * @brief Deletes the node at the given index
 * @param list: pointer to the list
 * @param index: index of the node to be deleted
 * @note internally calls ll_node_destroyer() or the custom destroyer function
 * Time Complexity: O(n)
*/
void ll_delete_at(LinkedList* list, size_t index);


/**
 * @brief Inserts a new node at the given index
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @param index: index of the node to be inserted
 * @note The data will be shallow copied
 * Time Complexity: O(n)
*/
void ll_insert_at(LinkedList* list, void* data, size_t index);


/**
 * @brief Compares two nodes
 * @param node1: pointer to the first node
 * @param node2: pointer to the second node
 * @param size: size of each element in the list
 * @return int: 0 if equal, non zero otherwise
 * @note Internally calls memcmp()
*/
int ll_node_cmp(ll_node* node1, ll_node* node2, size_t size);


/**
 * @brief Removes the first node that matches the given data
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @param cmp: function pointer to the comparator function
 * @note The comparator function should have the following signature:
 *     int cmp(const void*, const void*, size_t)
 *         The first two parameters are the pointers to the data
 *         The third parameter is the size of each element in the list
 * @node Internally calls ll_node_destroyer() or the custom destroyer function
 * Time Complexity: O(n)
*/
void ll_remove_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t));


/**
 * @brief Removes the first node that matches the given data
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @note Internally calls ll_remove_cmp()
 * Time Complexity: O(n)
*/
void ll_remove(LinkedList* list, void* data);


/**
 * @brief Removes node comparing the address of the node from the list
 * @param list: pointer to the list
 * @param node: pointer to the node
 * @note Internally calls ll_node_destroyer() or the custom destroyer function
 * Time Complexity: O(n)
*/
void ll_remove_node(LinkedList* list, ll_node* node);


/**
 * @brief Sets the data of the node
 * @param node: pointer to the node
 * @param data: pointer to the data
 * @param size: size of each element in the list
 * @note The data will be shallow copied
 * @note Internally calls memcpy()
 * Time Complexity: O(1)
*/
void ll_set_node_data(ll_node* node, void* data, size_t size);


/**
 * @brief Erases the node after the given node
 * @param list: pointer to the list
 * @param node: pointer to the node
 * @note Internally calls ll_node_destroyer() or the custom destroyer function
 * Time Complexity: O(1)
*/
void ll_erase_after(LinkedList* list, ll_node* node);


/**
 * @brief Erases the node after the node at the given index
 * @param list: pointer to the list
 * @param index: index of the node
 * @note Internally ll_erase_after and ll_destroyer() or the custom destroyer function
 * Time Complexity: O(n)
*/
void ll_erase_after_index(LinkedList* list, size_t index);


/**
 * @brief Returns the node at the given index
 * @param list: pointer to the list
 * @param index: index of the node
 * Time Complexity: O(n)
 * @note Returns NULL if the index is out of range or the list is empty
 * Time Complexity: O(n)
*/
ll_node* ll_node_at(LinkedList* list, size_t index);


/**
 * @brief Similar to ll_node_at()
 * @note Internally calls ll_node_at()
 * Time Complexity: O(n)
*/
ll_node* ll_get_node_at(LinkedList* list, size_t index);


/**
 * @brief Returns the node that matches the given data
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @param cmp: function pointer to the comparator function
 * @note The comparator function should have the following signature:
 *    int cmp(const void*, const void*, size_t)
 *    The first two parameters are the pointers to the data
 *    The third parameter is the size of each element in the list
 * Returns NULL if the data is not found
 * Time Complexity: O(n)
*/
ll_node* ll_get_node_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t));


/**
 * @brief Returns the node that matches the given data
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @note Internally calls ll_get_node_cmp() with memcmp as the comparator function
 * Returns NULL if the data is not found
 * Time Complexity: O(n)
*/
ll_node* ll_get_node(LinkedList* list, void* data);


/**
 * @brief Returns the data of the node at the given index
 * @param list: pointer to the list
 * @param index: index of the node
 * Internally calls ll_get_node()
 * Returns NULL if not found
 * Time Complexity: O(n)
*/
void* ll_get(LinkedList* list, void* data);


/**
 * @brief Similar to ll_get_node()
 * @note Internally calls ll_get_node()
 * Time Complexity: O(n)
*/
ll_node* ll_find(LinkedList* list, void* data);


/**
 * @brief Similar to ll_get_node_cmp()
 * @note Internally calls ll_get_node_cmp()
 * Time Complexity: O(n)
*/
ll_node* ll_find_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t));


/**
 * @brief Returns the data of the node at the given index
 * @param list: pointer to the list
 * @param index: index of the node
 * @note Internally calls ll_at()
 * Time Complexity: O(n)
*/
void* ll_data_at(LinkedList* list, size_t index);


/**
 * @brief Returns the data of the node
 * @param node: pointer to the node
 * @note returns node -> data
 * Time Complexity: O(1)
*/
void* ll_data(ll_node* node);


/**
 * @brief Sets the data of the node
 * @param node: pointer to the node
 * @param data: pointer to the data
 * @note The data will be shallow copied
 * @note Internally calls memcpy()
 * Time Complexity: O(1)
*/
void ll_set_node_data(ll_node* node, void* data, size_t size);


/**
 * @brief Sets the data of the node at the given index
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @param index: index of the node
 * @note The data will be shallow copied
 * @note Internally calls ll_at() and memcpy()
 * Time Complexity: O(n)
*/
void ll_set_at(LinkedList* list, size_t index, void* data);


/**
 * @brief Returns 1 if the list contains the given data, 0 otherwise
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @param cmp: function pointer to the comparator function
 * @note The comparator function should have the following signature:
 *    int cmp(const void*, const void*, size_t)
 *       The first two parameters are the pointers to the data
 *       The third parameter is the size of each element in the list
 * Time Complexity: O(n)
*/
int ll_contains_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t));


/**
 * @brief Returns 1 if the list contains the given data, 0 otherwise
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @note Internally calls ll_contains_cmp() with memcmp as the comparator function
 * Time Complexity: O(n)
*/
int ll_contains(LinkedList* list, void* data);


/**
 * @brief Returns 1 if the list contains the given node, 0 otherwise
 * @param list: pointer to the list
 * @param node: pointer to the node
 * @note Checks the address of the node
 * Time Complexity: O(n)
*/
int ll_contains_node(LinkedList* list, ll_node* node);


/**
 * @brief Reverse the list
 * @param list: pointer to the list
 * Time Complexity: O(n)
*/
void ll_reverse(LinkedList* list);


/**
 * @brief Returns 1 if the list is empty, 0 otherwise
 * @param list: pointer to the list
 * Time Complexity: O(1)
*/
int ll_is_empty(LinkedList* list);


/**
 * @brief Returns the address of the head node
 * @param list: pointer to the list
 * @note returns list -> head
 * Time Complexity: O(1)
*/
ll_node* ll_begin(LinkedList* list);


/**
 * @brief Returns the address of the tail node
 * @param list: pointer to the list
 * @note returns list -> tail
 * Time Complexity: O(1)
*/
ll_node* ll_end(LinkedList* list);


/**
 * @brief Returns void pointer to the data of the head node
 * @param list: pointer to the list
 * @note returns list -> head -> data
 * Time Complexity: O(1)
*/
void* ll_front(LinkedList* list);


/**
 * @brief Returns void pointer to the data of the tail node
 * @param list: pointer to the list
 * @note returns list -> tail -> data
 * Time Complexity: O(1)
*/
void* ll_back(LinkedList* list);


/**
 * @brief Clears the list
 * @param list: pointer to the list
 * @note Internally calls ll_node_destroyer() or the custom destroyer function
 * Time Complexity: O(n)
*/
void ll_clear(LinkedList* list);



/**
 * @brief Returns the index of the first node that matches the given data
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @param cmp: function pointer to the comparator function
 * @note The comparator function should have the following signature:
 *   int cmp(const void*, const void*, size_t)
 *       The first two parameters are the pointers to the data
 *       The third parameter is the size of each element in the list
 * Time Complexity: O(n)
*/
size_t ll_index_of_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t));



/**
 * @brief Returns the index of the first node that matches the given data
 * @param list: pointer to the list
 * @param data: pointer to the data
 * @note Internally calls ll_index_of_cmp() with memcmp as the comparator function
 * Time Complexity: O(n)
*/
size_t ll_index_of(LinkedList* list, void* data);


/**
 * @brief Returns the index of the first node that matches the given node
 * @param list: pointer to the list
 * @param node: pointer to the node
 * @note Checks the address of the node
 * @note Returns -1 if the node is not found
 * Time Complexity: O(n)
*/
size_t ll_index_of_node(LinkedList* list, ll_node* node);


/**
 * @brief Swaps two LinkedLists
 * @param list1: pointer to the first list
 * @param list2: pointer to the second list
 * Time Complexity: O(1)
*/
void ll_swap(LinkedList* list1, LinkedList* list2);


#endif