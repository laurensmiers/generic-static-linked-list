#include "ll_uintptr.h"

void ll_add_node(uintptr_t *root, uintptr_t new_node)
{
  uintptr_t temp=0, end=0;

  if (!*root || !new_node) {
    *root = new_node;
    new_node = 0;
  }

  temp = *root;
  do {
    if (temp == new_node) {
      return;
    }
    end = temp;
    temp = *(uintptr_t *)temp;
  } while(temp);

  *(uintptr_t *)end = new_node;
  
  return;
}

void ll_remove_node(uintptr_t *root, uintptr_t node)
{
  uintptr_t prev=0, curr=0;

  if (!root || !node) {
    return;
  }

  curr = *root;
  do {
    if (curr == node) {
      break;
    }
    prev = curr;
    curr = *(uintptr_t *)curr;
  } while(curr);
  
  /* element not found */
  if (!curr)
    return;

  if (!prev) {
    /* Trying to delete root */
    *(uintptr_t *)root = *(uintptr_t *)curr;    
  } else {
    /* Normal deletion */
    *(uintptr_t *)prev = *(uintptr_t *)curr;
  }
}
