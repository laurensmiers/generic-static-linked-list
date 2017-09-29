#ifndef _LL_UINTPTR_H
#define _LL_UINTPTR_H

#include <stdint.h>

/* void ll_add_node(ll_t **root, ll_t *new_node); */
void ll_add_node(uintptr_t *root, uintptr_t new_node);

/* void ll_remove_node(ll_t **root, ll_t *new_node); */
void ll_remove_node(uintptr_t *root, uintptr_t new_node);

#endif // _LL_UINTPTR_H
