void save_node(node* n, FILE* f){
  fwrite(n->val, n->size_of_elt,n->len,f);
}

int save_buffer(buffer b, const char* pathname){
  FILE *stream = fopen(pathname, 'w');
  node *temp = b->head;
  while(temp != NULL){
    save_node(temp, stream);
    temp = temp->next;
  }
}
    
  
