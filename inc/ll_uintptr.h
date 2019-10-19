#pragma once

#include <stdbool.h>

/**
 * A for-each convience macro
 * @note it is NOT safe to manipulate the list (removing elements) in this loop, use @ref ll_foreach_safe for this
 *
 * @param[in] root Pointer to a root node that was initialized with @ref ll_init
 * @param[in] idx Pointer to a node which can be used as iterator in the loop body
 */
#define ll_foreach(root, idx)                               \
                for ((idx) = (root)->next;                  \
                     (idx) != (root) && (idx) != NULL;      \
                     (idx) = (idx)->next)

/**
 * A for-each convience macro which is safe to use to manipulate the list
 *
 * @param[in] root Pointer to a root node that was initialized with @ref ll_init
 * @param[in] idx Pointer to a node which can be used as iterator in the loop body
 */
#define ll_foreach_safe(root, idx, idx2)                                                              \
                for ((idx) = (root)->next;                                                            \
                     (idx) != (root) && (idx) != NULL && (((idx2) = (idx)->next),1); \
                     (idx) = (idx2))

struct ll_node {
        struct ll_node *next;
        struct ll_node *prev;
};

/**
 * Intialize a linked list root node
 * Note that the root node should not be part of entities(struct's, ...) you will use to populate the list.
 * It is a separate entity which is used for bookkeeping and is not considered part of the list.
 *
 * @param[in] The node to initialize as root
 */
void ll_init(struct ll_node *root);

/**
 * Push a node to the end of the list
 * It will become the new tail of the list.
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 * @param[in] The node to push to the end of the list
 * @return An errorcode
 * @retval 0 if success
 * @retval < 0 if an error occurs (bad params, ...)
 */
int ll_push_to_tail(struct ll_node *root, struct ll_node *new_node);

/**
 * Push a node to the beginning of the list.
 * It will become the new head of the list.
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 * @param[in] The node to push to the head of the list
 * @return An errorcode
 * @retval 0 if success
 * @retval < 0 if an error occurs (bad params, ...)
 */
int ll_push_to_head(struct ll_node *root, struct ll_node *new_node);

/**
 * Remove a node of the list.
 * @note It is not intended to remove the root-node like this.
 *       Use @ref ll_deinit for removing a root node.
 *
 * @param[in] The node to remove from the list
 * @return An errorcode
 * @retval 0 if success
 * @retval < 0 if an error occurs (bad params, ...)
 */
int ll_remove_node(struct ll_node *node);

/**
 * Retrieve the next element in the list
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 * @param[in] The node to use to get the next node from
 * @return A pointer to the next node in the list
 * @retval NULL if the end of the list is reached
 */
int ll_indexof(struct ll_node *root, struct ll_node *node);

/**
 * Count the number of elements in the list
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 * @return The number of elements in the list
 * @retval < 0 if an error occured (bad params...)
 */
int ll_count(struct ll_node *root);

/**
 * Check if a node is linked in the list
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 * @param[in] The node to check
 * @return A bool flag
 * @retval true if the node is part of the list
 * @retval false if the node is NOT part of the list
 */
bool ll_is_linked(struct ll_node *root, struct ll_node *node);

/**
 * Check if a list is empty
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 * @return A bool flag
 * @retval true if the list is empty
 * @retval false if the list is NOT empty
 */
bool ll_is_empty(struct ll_node *root);

/**
 * Check if a node is the last element in the list
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 * @param[in] The node to check
 * @return A bool flag
 * @retval true if the node is the last element/tail of the list
 * @retval false if the node is NOT the last element/tail of the list
 */
bool ll_is_tail(struct ll_node *root, struct ll_node *node);

/**
 * Deinitialize a root node/list
 * @pre root node initialized with @ref ll_init
 *
 * @param[in] The root node of the list
 */
void ll_deinit(struct ll_node *root);
