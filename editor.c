#include "editor.h"
#include <string.h>
#include <signal.h>
#include <unistd.h>
    
buffer* buffer_construct(){
  buffer* b = (buffer*)malloc(sizeof(buffer));
  b->line_nums = 1;
  b->head = list_construct("\n", sizeof(char), 1);
  b->curr = b->head;
  b->end = b->head;
  return b;
}

void buffer_destruct(buffer* b){
  list_destruct(b->head);
  free(b);
}

void edit_buffer(buffer* b){  
  char str[MAX] = {0}, input = '\0';
  int i = 0; // Counter for length of string

  // Loop until we get Ctrl-D
  while(input != '\004') {
    // If we exceed our maximum length, make a new node
    // in our linked list.
    if(i == MAX-2){
      str[i+1] = '\n';
      b->curr = add(b->head, (void*)str, sizeof(*str), 1);
      i = 0;            
    }
    
    // Start a new node if the user inputs a '\n'
    else if(input == '\n') {
      str[i] = input;
      b->curr = add(b->head, (void*)str, sizeof(*str), i+1);
      i = 0;
      input = '\0';
    }

    // Save on Ctrl-A
    else if(input == '\001') {
      save_buffer(b, "temp.txt");
      i = 0;
    }
    
    else if(input == 127 || input == 8){  // If input is BCKSPCE or DLT
      i--;
      printf("\b \b");  // Move back, overwrite with SPCE, then move back again
    }

    // Scan input, character by character
    read(STDIN_FILENO, &input, 1);    
    str[i] = input;    
    i++;
  }
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

int save_node(node* n, FILE* f){
  return fwrite(n->val, n->size,n->len,f);
}
