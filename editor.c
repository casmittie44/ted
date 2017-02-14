#include "editor.h"
#include <string.h>
#include <signal.h>
int save_node(node* n, FILE* f){
  return fwrite(n->val, n->size,n->len,f);
}

int save_buffer(buffer* b, const char* pathname){
  FILE *stream = fopen(pathname, "r+");
  node *temp = b->head;
  while(temp != NULL){
    save_node(temp, stream);
    temp = temp->next;
  }

  return fclose(stream);
}
    
buffer* buffer_construct(){
  buffer* b = (buffer*)malloc(sizeof(buffer));
  b->line_nums = 1;
  b->head = list_construct("\n", sizeof(char), 10);
  b->curr = b->head;
  b->end = b->head;
  return b;
}

void buffer_destruct(buffer* b){
  list_destruct(b->head);
  free(b);
}

void edit_buffer(buffer* b){  
  char str[MAX], input = '\0';
  int i = 0; // Counter for length of string
  while(1) {
    // If we exceed our maximum length, make a new node
    // in our linked list.
    if(i == MAX-2){
      str[i+1] = '\n';
      node_modify(b->curr, str, sizeof(*str), i+1);
      b->curr = add(b->head, (void*)str, sizeof(*str), 1);
      i = 0;            
    }
    
    // Start a new node if the user inputs a '\n'
    else if(input == '\n') {
      node_modify(b->curr , str, sizeof(*str), i+1);
      b->curr = add(b->head, (void*)str, sizeof(*str), 1);
      i = 0;
      input = '\0';
    }
    
    // Scan input, character by character
    scanf("%c", &input);    
    str[i] = input;    
    i++;
  }

  save_buffer(b, "temp.txt");
}

char* add_newline(char* str, int len){
  int i = 0;
  while(str[i] != '\0')
      i++;
  str[i+1] = '\n';
  str[i+2] = '\0';
  
  return str;
}
  
