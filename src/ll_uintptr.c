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

  temp = *root;

  ll_foreach(temp, *root, offset) {
    if (temp == new_node) {
      return ll_status_OK;
    }
    end = temp;
  }

  *(uintptr_t *)(end + offset) = new_node;

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

  ll_foreach(curr, *root, offset) {
    if (curr == node) {
      break;
    }
    prev = curr;
  }

  /* element not found */
  if (!curr) {
    return ll_status_Error;
  }

  if (curr == *root) {
    /* Trying to delete root */
    *(uintptr_t *)root = *(uintptr_t *)(curr + offset);
  } else {
    /* Normal deletion */
    *(uintptr_t *)(prev + offset) = *(uintptr_t *)(curr + offset);
  }

  *(uintptr_t *)(curr + offset) = 0;

  return ll_status_OK;
}

uintptr_t ll_next_node(uintptr_t node, uint32_t offset)
{
    if (!node) {
        return (uintptr_t)NULL;
    }

    return *(uintptr_t *)(node + offset);
}
