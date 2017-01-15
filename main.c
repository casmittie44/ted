#include "editor.h"
int main(int argc, char** argv) {
  buffer* b = buffer_construct();
  edit_buffer(b);
  buffer_destruct(b);
  return 0;
}
