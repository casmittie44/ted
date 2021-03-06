#ifndef NODE_H
#define NODE_H

typedef struct node {
  int size;   // Size of each elment
  int len;    // Number of elements
  void *val;  // Pointer to elements
  struct node *prev;
  struct node *next;
} node;

void* car(node *n);           
node* cdr(node *n);         
node* list_construct(void* value, int size, int length);       
void* cpyptr(void*, int size, int length);
node* get_last(node* head);
node* get_ith(node* head, int index);
void list_destruct(node* head);
node* add(node* head,void* new, int size, int length);
void node_modify(node*,void*, int, int);
void insert_subseq(node*,node*,int);
void print(node*);  
#endif
