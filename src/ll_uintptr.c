#include "ll_uintptr.h"

void ll_add_node(uintptr_t *root, uintptr_t new_node, uint32_t offset)
{
  uintptr_t temp=0, end=0;

  if (!*root || !new_node) {
    *root = new_node;
    *(uintptr_t *)((uintptr_t)new_node + offset) = 0;
    return;
  }

  temp = *root + offset;
  do {
    if (temp - offset == new_node) {
      return;
    }
    end = temp;
    temp = *(uintptr_t *)(temp) + offset;
  } while(temp - offset);

  *(uintptr_t *)end = new_node;
  
  return;
}

void ll_remove_node(uintptr_t *root, uintptr_t node, uint32_t offset)
{
  uintptr_t prev=0, curr=0;

  if (!root || !node) {
    return;
  }

  prev = *root;
  curr = *root + offset;
  do {
    if (curr - offset == node) {
      break;
    }
    prev = curr;
    curr = *(uintptr_t *)(curr) + offset;
  } while(curr - offset);
  
  /* element not found */
  if (!(curr - offset))
    return;

  if (prev == *root) {
    /* Trying to delete root */
    *(uintptr_t *)root = *(uintptr_t *)curr;
  } else {
    /* Normal deletion */
    *(uintptr_t *)prev = *(uintptr_t *)curr;
  }
}
