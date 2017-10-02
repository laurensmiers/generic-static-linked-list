#include "ll_uintptr.h"
#include <stddef.h>

ll_status_t ll_append_node(uintptr_t *root, uintptr_t new_node, uint32_t offset)
{
    uintptr_t temp=0, end=0;

    if (!root || !new_node) {
        /* Bad param provided */
        return ll_status_Error;
    }

    if (!*root) {
        /* root is not defined yet, new_node will be root  */
        *root = new_node;
        *(uintptr_t *)((uintptr_t)new_node + offset) = 0;
        return ll_status_OK;
    }

    ll_foreach(*root, temp, offset) {
        if (temp == new_node) {
            /* new_node is already in */
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
        /* Bad param provided */
        return ll_status_Error;
    }

    if (!*root) {
        /* Bad param provided, root is not set? */
        return ll_status_Error;
    }

    ll_foreach(*root, curr, offset) {
        if (curr == node) {
            break;
        }
        prev = curr;
    }

    if (!curr) {
        /* element not found */
        return ll_status_Error;
    }

    if (curr == *root) {
        /* Trying to delete root, reposition root */
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
        /* Bad param provided */
        return (uintptr_t)NULL;
    }

    return *(uintptr_t *)(node + offset);
}

int ll_indexof(uintptr_t *root, uintptr_t node, uint32_t offset)
{
    uintptr_t curr=0;
    int i = 0;

    if (!root || !node) {
        /* Bad param provided */
        return -1;
    }

    if (!*root) {
        /* Bad param provided */
        return -1;
    }

    ll_foreach(*root, curr, offset) {
        if (curr == node) {
            /* node found */
            return i;
        }
        i++;
    }

    return -1;
}
