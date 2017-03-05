#include "void_node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  Return the value of a node. This function does NOT check if the node is NULL. 
  If it is NULL, the program will crash. Don't say I didn't warn you. Unlike the cdr function,
  this function actually is not that useful, but it is included for consistency.
*/
void* car(node *n) {
  return n->val;
}

/* 
   Returns pointer to the next node in the list. This function DOES check that the passed
   node is not NULL. If it is, it returns NULL. This function is nice because it allows us to 
   avoid checking if a node is null before looking up the next value.
*/
node* cdr(node *n) {
  if(n == NULL)
    return NULL;
  else
    return (node*)n->next;
}

void* cpyptr(void *ptr, int size, int len) {
  void *ret = malloc(size*len);
  memcpy(ret, ptr, size*len);
  return ret;
}

/* 
   Create a new node using malloc. The new node will have the given value
   and will have a next value of NULL.
*/
node* list_construct(void* value, int size, int length) {
  node *new = (node*)malloc(sizeof(node));
  new->size = size;
  new->len = length;
  new->val = cpyptr(value, size, length);
  new->next = NULL;
  return new;
}

/*
  This function gets the last element of a linked list.
  If the head parameter is NULL, a value of NULL is returned.
*/
node* get_last(node* head) {
  node* ret = head;
  while(cdr(ret) != NULL) 
    ret = cdr(ret);
  return ret;
}

/*
  This function gets the node with the passed index. 
  The head node is considered to have index 0.
*/
node* get_ith(node *head, int index) {
  int i = 0;
  node *curr = (node*)head;
  while(curr != NULL && i != index){
    curr = cdr(curr);
    ++i;
  }
  
  return curr;   
}
  
  
/*
  This function frees all elements of a linked list with first element head 
*/
void list_destruct(node *head) {  
  node *curr = head;
  node *next = cdr(head);
  while(curr != NULL){
    free(curr->val);
    free(curr);
    curr = next;
    next = cdr(next);    
  }
}

/* 
   This function adds a node with the given value to the end of the linked list.
   It returns the head of the list, with the new node attached.
   If the passed list is NULL, a new list is constructed. When calling this function
  with head values that may be NULL, it is important that it NOT be called only for its side effect; 
   it should be called like this:
       head = add(head, 10);
   This ensures that, if head == NULL we will capture the newly constructed list.
*/
node* add(node *head, void* value, int size, int length) {
  if(head == NULL)
    return list_construct(value, size, length);
  
  else {
    node *end = get_last(head);
    node *new = (node*)malloc(sizeof(node));
    new->size = size;
    new->len = length;
    new->val = cpyptr(value, size, length);
    new->prev = end;
    new->next = NULL;
    end->next = (node*)new;
    return head;
  }
}

/*
  This function inserts the linked list  beginning with subseq into the list beginning with head.
  It is inserted after the node with index "position", where head has index 0.
*/
void insert_subseq(node* head, node* subseq, int position) {
  if(head == NULL)
    return;
  node *curr, *next, *end;
  curr = get_ith(head, position);
  next = (node*)curr->next;
  end = get_last(subseq);
  curr->next = (node*)subseq;
  end->next = (node*)next;
}

/* 
   This function prints every element of the linked list, separated by newlines.
   It then prints the number of nodes in the list.
*/
void print(node *head){
  node *curr = head;
  int count = 0;
  while(curr != NULL){
    printf("Value: %s\n", (char*)curr->val);
    curr = (node*)curr->next;
    count++;
  }
  
  printf("Total nodes: %u\n", count);
}

/*
  Replaces the value, size, and length fields of the passed node with
  new values.
 */
void node_modify(node* curr, void *new_val, int size, int length){
  if(curr != NULL){
    free(curr->val);
    curr->val = cpyptr(new_val, size, length);
    curr->size = size;
    curr->len = length;
  }
}
