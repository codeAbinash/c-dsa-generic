/*
*  Library file for Singly Linked List
*  Author: Abinash Karmakar
*  https://github.com/codeAbinash/c-ds-algo-crafts
*  2023-08-28 MIT License Version: 1.0
*/

#include "malloc.h"
#include "string.h"
#include "assert.h"
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
   size_t size;
   ll_node* head;
   ll_node* tail;
   size_t element_size;
   void (*destroyer)(ll_node*);
} LinkedList;


LinkedList ll_init_with_destroyer(size_t element_size, void (*destroyer)(ll_node*)) {
   LinkedList list;
   list.size = 0;
   list.head = NULL;
   list.tail = NULL;
   list.element_size = element_size;
   list.destroyer = destroyer;
   return list;
}


LinkedList ll_init(size_t element_size) {
   return ll_init_with_destroyer(element_size, NULL);
}


ll_node* ll_create_node(LinkedList* list, void* data) {
   ll_node* new_node = (ll_node*)malloc(sizeof(ll_node));
   assert(new_node && "Not Enough Memory!");
   new_node->data = malloc(list->element_size);
   assert(new_node->data && "Not Enough Memory!");
   memcpy(new_node->data, data, list->element_size);
   new_node->next = NULL;
   return new_node;
}


size_t ll_size(LinkedList* list) {
   return list->size;
}


// For Destroying only one node
void ll_node_destroyer(ll_node* node) {
   free(node->data); // Free the data that is allocated when creating the node
   free(node); // Free the node itself
};


void ll_node_free(ll_node* node) {
   ll_node_destroyer(node);
}

int ll_is_empty(LinkedList* list) {
   return list->size == 0;
}


ll_node* ll_end(LinkedList* list) {
   return list->tail;
}


ll_node* ll_begin(LinkedList* list) {
   return list->head;
}


void* ll_front(LinkedList* list) {
   return list->head->data;
}


void* ll_back(LinkedList* list) {
   return list->tail->data;
}



void _ll_node_destroyer(void (*destroyer)(ll_node*), ll_node* node) {
   if (destroyer)
      destroyer(node);
   else
      ll_node_destroyer(node);
}


// Destroying the whole list
void ll_destroyer(LinkedList* list) {
   ll_node* curr = list->head;
   ll_node* next;
   while (curr) {
      next = curr->next;
      // Destroy each node
      _ll_node_destroyer(list->destroyer, curr);
      curr = next;
   }
   // Reset the list
   list->head = NULL;
   list->tail = NULL;
   list->size = 0;
   list->element_size = 0;
   list->destroyer = NULL;
}


void ll_free(LinkedList* list) {
   ll_destroyer(list);
}


// For Each element in the list call the callback function
void ll_for_each(LinkedList* list, void (*callback)(ll_node*, size_t)) {
   ll_node* curr = list->head;
   size_t i = 0;
   while (curr) {
      // Call the callback function with the current node and the index
      callback(curr, i++);
      curr = curr->next;
   }
}


// Insertion at the beginning 
void ll_push_front(LinkedList* list, void* data) {
   ll_node* new_node = ll_create_node(list, data);
   new_node->next = list->head;
   list->head = new_node;
   // If the list was empty, the tail should point to the new node
   if (list->tail == NULL)
      list->tail = new_node;
   list->size++;
}


// Deletion at the beginning
void ll_pop_front(LinkedList* list) {
   assert(list->head && "Cannot Delete, Empty List!");
   ll_node* oldHead = list->head;
   list->head = list->head->next;
   // If the list is empty after deleting the head, the tail should be NULL
   if (list->head == NULL)
      list->tail = NULL;
   _ll_node_destroyer(list->destroyer, oldHead);
   list->size--;
}


// Insertion at the end
void ll_push_back(LinkedList* list, void* data) {
   ll_node* new_node = ll_create_node(list, data);
   // if there is no item in the list i.e. head == NULL
   if (list->head == NULL) {
      list->head = new_node;
      list->tail = new_node;
      list->size++;
      return;
   }
   // Last Node found, now insert the new node to it's -> next
   list->tail->next = new_node;
   list->tail = new_node;
   list->size++;
}


// Deletion at the end
void ll_pop_back(LinkedList* list) {
   assert(list->size && "Cannot Delete, Empty List!");
   ll_node* curr = list->head, * prev = NULL;
   // If there is only one item in the list
   if (list->head == list->tail) {
      list->head = NULL;
      list->tail = NULL;
      list->size = 0;
      _ll_node_destroyer(list->destroyer, curr);
      return;
   }
   // Find the last node
   while (curr->next) {
      prev = curr;
      curr = curr->next;
   }
   _ll_node_destroyer(list->destroyer, curr);
   // Set the new tail
   list->tail = prev;
   list->tail->next = NULL;
   list->size--;
}


// Deletion at a given index
void ll_delete_at(LinkedList* list, size_t index) {
   size_t size = list->size;
   ll_node* curr = list->head, * nextNode = NULL;
   size_t i = 1;
   // Delete at beginning, shift
   if (index == 0) {
      ll_pop_front(list);
      return;
   }
   // Delete at end, pop
   if (index == size - 1) {
      ll_pop_back(list);
      return;
   }
   // Invalid Index
   assert(size > index && "Invalid Index");
   // Delete in between, find the node at index - 1
   while (i < index) {
      curr = curr->next;
      i++;
   }
   nextNode = curr->next->next;
   // If there is a destroyer function, call it
   _ll_node_destroyer(list->destroyer, curr->next);
   curr->next = nextNode;
   list->size--;
}


// Insertion at a given index
void ll_insert_at(LinkedList* list, void* data, size_t index) {
   size_t size = list->size;
   ll_node* new_node, * curr_node = list->head;
   size_t i = 1;
   // Insert at beginning, unshift
   if (index == 0) {
      ll_push_front(list, data);
      return;
   }
   // Insert at end, push
   if (index == size) {
      ll_push_back(list, data);
      return;
   }
   // Invalid Index
   assert(size > index && "Invalid Index");
   // Insert in between, find the node at index - 1
   new_node = ll_create_node(list, data);
   while (i < index) {
      curr_node = curr_node->next;
      i++;
   }
   new_node->next = curr_node->next;
   curr_node->next = new_node;
   list->size++;
}


int ll_node_cmp(ll_node* node1, ll_node* node2, size_t size) {
   return memcmp(node1->data, node2->data, size);
}


// Remove all the occurrences of a given data
void ll_remove_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t)) {
   ll_node* curr = list->head, * prev = NULL, * next = NULL;
   while (curr) {
      next = curr->next;
      if (cmp(curr->data, data, list->element_size) == 0) {
         if (prev == NULL) {
            ll_pop_front(list);
            curr = list->head;
            continue;
         } else if (next == NULL) {
            ll_pop_back(list);
            curr = list->tail;
            continue;
         } else {
            prev->next = next;
            _ll_node_destroyer(list->destroyer, curr);
            list->size--;
            curr = prev;
         }
      }
      prev = curr;
      curr = next;
   }
}


void ll_remove(LinkedList* list, void* data) {
   ll_remove_cmp(list, data, memcmp);
}


void ll_remove_node(LinkedList* list, ll_node* node) {
   ll_node* curr = list->head, * prev = NULL, * next = NULL;
   while (curr) {
      next = curr->next;
      if (curr == node) {
         if (prev == NULL) {
            ll_pop_front(list);
            curr = list->head;
            continue;
         } else if (next == NULL) {
            ll_pop_back(list);
            curr = list->tail;
            continue;
         } else {
            prev->next = next;
            _ll_node_destroyer(list->destroyer, curr);
            list->size--;
            curr = prev;
         }
      }
      prev = curr;
      curr = next;
   }
}


void ll_set_node_data(ll_node* node, void* data, size_t size) {
   memcpy(node->data, data, size);
}


// Deletes all the nodes after a given node
void ll_erase_after(LinkedList* list, ll_node* node) {
   ll_node* curr = node->next, * next = NULL;
   while (curr) {
      next = curr->next;
      _ll_node_destroyer(list->destroyer, curr);
      curr = next;
      list->size--;
   }
   node->next = NULL;
   list->tail = node;
}


void ll_erase_after_index(LinkedList* list, size_t index) {
   ll_node* curr = list->head, * next = NULL;
   size_t i = 0;
   // Invalid Index
   assert(list->size > index && "Invalid Index");
   // Find the node at index
   while (i < index) {
      curr = curr->next;
      i++;
   }
   ll_erase_after(list, curr);
}


// Get the node at a given index
ll_node* ll_node_at(LinkedList* list, size_t index) {
   size_t size = list->size;
   ll_node* curr = list->head;
   size_t i = 0;
   // Invalid Index
   assert(size > index && "Invalid Index");
   // Find the node at index
   while (i < index) {
      curr = curr->next;
      i++;
   }
   return curr;
}

// Get the node with the given data using the given comparator
ll_node* ll_get_node_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t)) {
   ll_node* curr = list->head;
   while (curr) {
      if (cmp(curr->data, data, list->element_size) == 0)
         return curr;
      curr = curr->next;
   }
   return NULL;
}

// Get the node with the given data using memcmp
ll_node* ll_get_node(LinkedList* list, void* data) {
   return ll_get_node_cmp(list, data, memcmp);
}


ll_node* ll_get_node_at(LinkedList* list, size_t index) {
   return ll_node_at(list, index);
}


void* ll_get(LinkedList* list, void* data) {
   ll_node* node = ll_get_node(list, data);
   if (node)
      return node->data;
   return NULL;
}


ll_node* ll_find(LinkedList* list, void* data) {
   return ll_get_node(list, data);
}


ll_node* ll_find_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t)) {
   return ll_get_node_cmp(list, data, cmp);
}


void* ll_data_at(LinkedList* list, size_t index) {
   return ll_node_at(list, index)->data;
}


void* ll_data(ll_node* node) {
   return node->data;
}


void ll_set(ll_node* node, void* data) {
   memcpy(node->data, data, sizeof(data));
}


void ll_set_at(LinkedList* list, size_t index, void* data) {
   // FInd the node at index
   ll_node* node = ll_node_at(list, index);
   // Copy the data to the node
   memcpy(node->data, data, sizeof(data));
}


int ll_contains_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t)) {
   ll_node* curr = list->head;
   while (curr) {
      if (cmp(curr->data, data, list->element_size) == 0)
         return 1;
      curr = curr->next;
   }
   return 0;
}


size_t ll_index_of_cmp(LinkedList* list, void* data, int (*cmp)(const void*, const void*, size_t)) {
   ll_node* curr = list->head;
   size_t i = 0;
   while (curr) {
      if (cmp(curr->data, data, list->element_size) == 0)
         return i;
      curr = curr->next;
      i++;
   }
   return -1;
}


size_t ll_index_of(LinkedList* list, void* data) {
   return ll_index_of_cmp(list, data, memcmp);
}


int ll_contains(LinkedList* list, void* data) {
   return ll_index_of(list, data) != -1;
}


size_t ll_index_of_node(LinkedList* list, ll_node* node) {
   ll_node* curr = list->head;
   size_t i = 0;
   while (curr) {
      if (curr == node)
         return i;
      curr = curr->next;
      i++;
   }
   return -1;
}


// If the memory address of the node is same as the given node
int ll_contains_node(LinkedList* list, ll_node* node) {
   return ll_index_of_node(list, node) != -1;
}


void ll_swap(LinkedList* list1, LinkedList* list2) {
   LinkedList temp = *list1;
   *list1 = *list2;
   *list2 = temp;
}


void ll_reverse(LinkedList* list) {
   ll_node* prev = NULL, * curr = list->head, * next = NULL;
   list->tail = list->head;
   while (curr) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
   }
   list->head = prev;
}




// Remove all the elements from the list
void ll_clear(LinkedList* list) {
   ll_node* curr = list->head, * next = NULL;
   while (curr) {
      next = curr->next;
      _ll_node_destroyer(list->destroyer, curr);
      curr = next;
   }
   // Reset the list values
   list->head = NULL;
   list->tail = NULL;
   list->size = 0;
}

// End of LinkedList.c