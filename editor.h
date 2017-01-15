#ifndef EDITOR_H
#define EDITOR_H
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include "assets/void_node.h"

typedef struct buffer {
  int line_nums;
  node *curr, *head, *end;
} buffer;

buffer* buffer_construct();
void buffer_destruct(buffer*);
void edit_buffer(buffer*);
int save_node(node*, FILE*);
int save_buffer(buffer*, const char*);
char* add_newline(char*, int);
#endif


  
