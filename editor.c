#include "editor.h"
#include <string.h>
int save_node(node* n, FILE* f){
  return fwrite(n->val, n->size_of_elt,n->len,f);
}

int save_buffer(buffer* b, const char* pathname){
  FILE *stream = fopen(pathname, "w");
  node *temp = b->head;
  while(temp != NULL){
    save_node(temp, stream);
    temp = temp->next;
  }

  fclose(stream);
}
    
buffer* buffer_construct(){
  buffer* b = (buffer*)malloc(sizeof(buffer));
  b->line_nums = 1;
  b->head = list_construct("\n", sizeof(char), 10);
  b->curr = b->head;
  b->end = b->head;
}

void buffer_destruct(buffer* b){
  list_destruct(b->head);
  free(b);
}

void edit_buffer(buffer* b){
  char str[MAX], *ptr;
  while(1){
    ptr = gets(str);    
    add_newline(ptr, MAX);
    node_value_replace(b->curr, ptr, sizeof(char), strlen(ptr));
    save_buffer(b, "temp.txt");
  }
}

char* add_newline(char* str, int len){
  int i = 0;
  while(str[i] != '\0')
      i++;

  str[i+1] = '\n';
  str[i+2] = '\0';
  return str;
}
  
