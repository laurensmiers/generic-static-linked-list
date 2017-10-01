#include "ll_uintptr.h"
#include <stddef.h>

ll_status_t ll_append_node(uintptr_t *root, uintptr_t new_node, uint32_t offset)
{
  uintptr_t temp=0, end=0;

  if (!root || !new_node) {
    return ll_status_Error;
  }

  if (!*root) {
    *root = new_node;
    *(uintptr_t *)((uintptr_t)new_node + offset) = 0;
    return ll_status_OK;
  }

  temp = *root + offset;
  do {
    if (temp - offset == new_node) {
      return ll_status_OK;
    }
    end = temp;
    temp = *(uintptr_t *)(temp) + offset;
  } while(temp - offset);

  *(uintptr_t *)end = new_node;

  return ll_status_OK;
}

ll_status_t ll_remove_node(uintptr_t *root, uintptr_t node, uint32_t offset)
{
  uintptr_t prev=0, curr=0;

  if (!root || !node) {
    return ll_status_Error;
  }

  if (!*root) {
    return ll_status_Error;
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
  if (!(curr - offset)) {
    return ll_status_Error;
  }

  if (prev == *root) {
    /* Trying to delete root */
    *(uintptr_t *)root = *(uintptr_t *)curr;
    *(uintptr_t *)(prev + offset) = 0;
  } else {
    /* Normal deletion */
    *(uintptr_t *)prev = *(uintptr_t *)curr;
    *(uintptr_t *)curr = 0;
  }

  return ll_status_OK;
}

uintptr_t ll_next_node(uintptr_t node, uint32_t offset)
{
    if (!node) {
        return (uintptr_t)NULL;
    }

    return *(uintptr_t *)(node + offset);
}
