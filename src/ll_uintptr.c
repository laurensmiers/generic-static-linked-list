#include "ll_uintptr.h"
#include <stddef.h>

static int _insert(struct ll_node *new, struct ll_node *prev, struct ll_node *next)
{
        if (!new || !prev || !next) {
                /* Bad param provided */
                return -1;
        }

        new->next = next;
        new->prev = prev;
        prev->next = new;
        next->prev = new;

        return 0;
}

void ll_init(struct ll_node *root)
{
        if (!root)
                return;

        root->next = root;
        root->prev = root;
}

bool ll_is_empty(struct ll_node *root)
{
        return root == root->next;
}

int ll_push_to_tail(struct ll_node *root, struct ll_node *new_node)
{
        if (!root || !new_node) {
                /* Bad param provided */
                return -1;
        }

        return _insert(new_node, root->prev, root);
}

int ll_push_to_head(struct ll_node *root, struct ll_node *new_node)
{
        if (!root || !new_node) {
                /* Bad param provided */
                return -1;
        }

        return _insert(new_node, root, root->next);
}

struct ll_node* ll_next_node(struct ll_node *root, struct ll_node *node)
{
        if (!root || !node) {
                /* Bad param provided */
                return NULL;
        }

        if (root == node->next)
                return NULL;

        return node->next;
}

void ll_deinit(struct ll_node *root)
{
        if (!root)
                return;

        root->next = NULL;
        root->prev = NULL;
}

int ll_remove_node(struct ll_node *node)
{
        struct ll_node *prev, *next;

        if (!node) {
                /* Bad param provided */
                return -1;
        }

        prev = node->prev;
        next = node->next;

        prev->next = next;
        next->prev = prev;

        node->next = NULL;
        node->prev = NULL;

        return 0;
}

int ll_indexof(struct ll_node *root, struct ll_node *node)
{
        int i = 0;
        struct ll_node *curr = NULL;

        if (!root || !node) {
                /* Bad param provided */
                return -1;
        }

        ll_foreach(root, curr) {
                if (curr == node) {
                        /* node found */
                        return i;
                }
                i++;
        }

        return -1;
}

int ll_count(struct ll_node *root)
{
        struct ll_node *temp = NULL;
        int count = 0;

        if (!root)
                return 0;

        ll_foreach(root, temp) {
                count++;
        }

        return count;
}

bool ll_is_linked(struct ll_node *root, struct ll_node *node)
{
        struct ll_node *temp = NULL;

        if (!root || !node)
                return 0;

        ll_foreach(root, temp) {
                if (temp == node)
                        return true;
        }

        return false;
}

bool ll_is_tail(struct ll_node *root, struct ll_node *node)
{
        if (!root || !node)
                return 0;

        return node->next == root;
}
