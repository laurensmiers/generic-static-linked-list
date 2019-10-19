#ifndef _LL_UINTPTR_H
#define _LL_UINTPTR_H

#include <stdbool.h>

#define ll_foreach(root, idx)                               \
                for ((idx) = (root)->next;                  \
                     (idx) != (root) && (idx) != NULL;      \
                     (idx) = ll_next_node((root),(idx)))

#define ll_foreach_safe(root, idx, idx2)                                                              \
                for ((idx) = (root)->next;                                                            \
                     (idx) != (root) && (idx) != NULL && (((idx2) = ll_next_node((root), (idx))),1);  \
                     (idx) = (idx2))

struct ll_node {
        struct ll_node *next;
        struct ll_node *prev;
};

void ll_init(struct ll_node *root);

int ll_push_to_tail(struct ll_node *root, struct ll_node *new_node);

int ll_push_to_head(struct ll_node *root, struct ll_node *new_node);

int ll_remove_node(struct ll_node *node);

struct ll_node* ll_next_node(struct ll_node *root, struct ll_node *node);

int ll_indexof(struct ll_node *root, struct ll_node *node);

int ll_count(struct ll_node *root);

bool ll_is_linked(struct ll_node *root, struct ll_node *node);

bool ll_is_empty(struct ll_node *root);

bool ll_is_tail(struct ll_node *root, struct ll_node *node);

void ll_deinit(struct ll_node *root);

#endif // _LL_UINTPTR_H
