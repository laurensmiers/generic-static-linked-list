#ifndef _LL_UINTPTR_H
#define _LL_UINTPTR_H

#include <stdint.h>

typedef enum {
    ll_status_OK    = 0,
    ll_status_Error = 1,
    ll_status_Count,
} ll_status_t;

ll_status_t ll_append_node(uintptr_t *root, uintptr_t new_node, uint32_t offset);

ll_status_t ll_remove_node(uintptr_t *root, uintptr_t node, uint32_t offset);

uintptr_t ll_next_node(uintptr_t node, uint32_t offset);

#define ll_foreach(root, idx, offset)                               \
    for ((idx) = (root);                                            \
         (idx) != (typeof(idx))NULL;                                \
         (idx) = (typeof(idx))ll_next_node((uintptr_t)idx, offset))

#define ll_foreach_safe(root, idx, idx2, offset)                        \
    for ((idx) = (root);                                                \
         ((idx) != (typeof(idx))NULL) && ((idx2) = (typeof(idx))ll_next_node((uintptr_t)idx, offset), 1); \
         (idx) = (idx2))

#endif // _LL_UINTPTR_H
