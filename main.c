#include "editor.h"
#include <stdio.h>

int main(int argc, char** argv) {
  puts("Welcome to ted. Press Ctrl + Z to exit.");
  buffer* b = buffer_construct();
  edit_buffer(b);
  buffer_destruct(b);
  return 0;
}
