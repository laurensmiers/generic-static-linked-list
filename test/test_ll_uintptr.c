#include "unity.h"
#include "ll_uintptr.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define NUMBER (10)

struct my_struct {
        struct ll_node node;
        int a;
};

static struct my_struct test_list[NUMBER];

void setUp(void)
{
        memset(test_list, 0, sizeof(test_list));

        for(int i = 0; i < NUMBER; ++i) {
                test_list[i].a = i+1;
        }
}

void tearDown(void)
{
        ll_deinit(&test_list[0].node);
}

static void link_array(struct ll_node *root, struct my_struct *list)
{
        for(int i = 0; i < NUMBER; ++i) {
                ll_append_node(root, &list[i].node);
        }
}

#if 0
static void print_node(struct my_struct *l)
{
        printf("\n");
        printf("NODE, address: %p\n", &l->node);
        printf("next: %p\n", l->node.next);
        printf("prev: %p\n", l->node.prev);
        printf("a: %d\n", l->a);
        printf("\n");
}

static void print_arr(void)
{
        for(int i = 0; i < NUMBER; ++i) {
                print_node(&test_list[i]);
        }
}

static void print(struct my_struct *l)
{
        struct ll_node *root = &l->node;
        struct ll_node *temp = root;

        while (temp) {
                print_node((struct my_struct *)temp);
                temp = temp->next;

                if (temp == root)
                        break;
        }
}
#endif

void test_ll_add_node_paramCheck(void)
{
        struct ll_node root = { 0 };
        struct my_struct temp = {
                .node = (struct ll_node) { 0 },
                .a = 100,
        };

        TEST_ASSERT_MESSAGE(ll_append_node(NULL, &temp.node) == -1,
                            "Passing NULL should result in error code (1)"
                );

        TEST_ASSERT_MESSAGE(0 == memcmp(&temp.node,&(struct ll_node) { 0 }, sizeof(struct ll_node)), "node should remain unaltered (1)");
        TEST_ASSERT_MESSAGE(temp.a == 100, "node should remain unaltered (2)");

        /* Passing valid args, this requires a valid linked list */
        ll_init(&root);

        link_array(&root, test_list);

        TEST_ASSERT_MESSAGE(ll_append_node(&test_list[0].node, NULL) == -1,
                            "Passing NULL should result in error code (2)"
                );

        TEST_ASSERT_MESSAGE(ll_append_node(&test_list[0].node, &temp.node) == 0,
                            "Passing valid args should result in success status code"
                );

}

void test_ll_remove_node_paramCheck(void)
{
        struct ll_node root = { 0 };

        TEST_ASSERT_MESSAGE(ll_remove_node(NULL) == -1,
                            "Passing NULL should result in error code (1)"
                );

        /* Passing valid args, this requires a valid linked list */
        ll_init(&root);

        link_array(&root, test_list);

        TEST_ASSERT_MESSAGE(ll_remove_node(&test_list[1].node) == 0,
                            "Passing valid args should result in success status code"
                );
}

void test_ll_rootInit(void)
{
        struct ll_node root = { 0 };

        TEST_ASSERT_MESSAGE(NULL == root.prev, "Root node prev should be uninitialized at start");
        TEST_ASSERT_MESSAGE(NULL == root.next, "Root node next should be uninitialized at start");

        ll_init(&root);

        TEST_ASSERT_MESSAGE(&root == root.prev, "Root node prev should be uninitialized at start");
        TEST_ASSERT_MESSAGE(&root == root.next, "Root node next should be uninitialized at start");
}

void test_ll_AddingOneElement(void)
{
        struct ll_node root = { 0 };
        struct ll_node temp = { 0 };
        ll_init(&root);

        TEST_ASSERT_MESSAGE(0 == ll_append_node(&root, &temp), "Adding an element should be succesfull");

        TEST_ASSERT_MESSAGE(root.next == &temp, "link should be present");
        TEST_ASSERT_MESSAGE(root.prev == &temp, "link should be present");
        TEST_ASSERT_MESSAGE(temp.next == &root, "link should be present");
        TEST_ASSERT_MESSAGE(temp.prev == &root, "link should be present");
}

static void test_array_links(struct ll_node *root, struct my_struct *list, int number_of_elements)
{
        for(int i = 0; i < number_of_elements - 1; ++i) {
                TEST_ASSERT_MESSAGE(list[i].node.next == &list[i+1].node, "link should be fully complete");
        }
        TEST_ASSERT_MESSAGE(list[number_of_elements-1].node.next == root, "link should be fully complete");

        for(int i = number_of_elements-1; i >= 1; --i) {
                TEST_ASSERT_MESSAGE(list[i].node.prev == &list[i-1].node, "link should be fully complete");
        }

        TEST_ASSERT_MESSAGE(list[0].node.prev == root, "link should be fully complete");
}

void test_ll_AddingSeveralNodes(void)
{
        struct ll_node root = { 0 };
        ll_init(&root);

        link_array(&root, test_list);

        test_array_links(&root, test_list, NUMBER);
}

void test_ll_RemovingOneNode(void)
{
        struct ll_node root = { 0 };

        ll_init(&root);
        link_array(&root, test_list);

        test_array_links(&root, test_list, NUMBER);

        ll_remove_node(&test_list[1].node);

        TEST_ASSERT_MESSAGE(test_list[0].node.next == &test_list[2].node,
                            "removing node that is not root should NOT result in losing link"
                );
        TEST_ASSERT_MESSAGE(test_list[1].node.next == 0, "Link in removed node should be set to 0");

        for(int i = 2; i < NUMBER - 1; ++i) {
                TEST_ASSERT_MESSAGE(test_list[i].node.next == &test_list[i+1].node, "link should still be there");
        }
}

void test_ll_nextNode_paramCheck(void)
{
        struct ll_node root = { 0 };

        TEST_ASSERT_MESSAGE(ll_next_node(&root, NULL) == NULL,
                            "Passing NULL should return NULL"
                );

        ll_init(&root);
        ll_append_node(&root, &test_list[0].node);

        TEST_ASSERT_MESSAGE(ll_next_node(NULL, &test_list[0].node) == NULL,
                            "Passing NULL should return NULL"
                );


        TEST_ASSERT_MESSAGE(ll_next_node(&root, &test_list[0].node) == NULL,
                            "Passing valid linked list with only 1 member should result in next node being NULL"
                );

        ll_append_node(&root, &test_list[1].node);

        TEST_ASSERT_MESSAGE(ll_next_node(NULL, &test_list[0].node) == NULL,
                            "Passing NULL should return NULL"
                );

        TEST_ASSERT_MESSAGE(ll_next_node(&root, &test_list[0].node) == &test_list[1].node,
                            "Passing valid linked list with 2 members should result in next node being the one we just added"
                );
}

void test_ll_nextNode_TraverseFullList(void)
{
        struct ll_node root = { 0 };

        ll_init(&root);
        link_array(&root, test_list);

        for(int i = 0; i < NUMBER - 1; ++i) {
                TEST_ASSERT_MESSAGE(ll_next_node(&root, &test_list[i].node) == &test_list[i+1].node, "next_node should actually return next node");
        }
}

void test_ll_foreach(void)
{
        struct ll_node root = { 0 };
        struct ll_node *idx = NULL;
        int i = 0;

        ll_init(&root);

        ll_foreach(&root, idx) {
                TEST_FAIL_MESSAGE("If there are no elements in the list, foreach should not enter the body of the loop");
                i++;
        }

        link_array(&root, test_list);

        ll_foreach(&root, idx) {
                TEST_ASSERT_MESSAGE(idx == &test_list[i].node, "Foreach should cycle through linked list, what node is it pointing to?");
                i++;
        }
        TEST_ASSERT_MESSAGE(i == NUMBER, "Foreach should cycle through whole list (2)");
}

void test_ll_foreach_safe(void)
{
        struct ll_node root = { 0 };
        struct ll_node *idx = NULL;
        struct ll_node *idx_safe = NULL;
        int i = 0;

        ll_init(&root);

        ll_foreach(&root, idx) {
                TEST_FAIL_MESSAGE("If there are no elements in the list, foreach should not enter the body of the loop");
                i++;
        }

        link_array(&root, test_list);

        ll_foreach_safe(&root, idx, idx_safe) {
                TEST_ASSERT_MESSAGE(idx == &test_list[i].node, "Foreach should cycle through linked list, what node is it pointing to?");
                i++;
        }

        TEST_ASSERT_MESSAGE(i == NUMBER, "Foreach_safe should cycle through whole list");
}

void test_ll_foreach_safe_RemovalOfNode(void)
{
        struct ll_node root = { 0 };
        struct ll_node *idx = NULL;
        struct ll_node *idx_safe = NULL;
        int i = 0;

        ll_init(&root);
        link_array(&root, test_list);

        ll_foreach_safe(&root, idx, idx_safe) {
                /* Delete first element */
                if (i == 0) {
                        ll_remove_node(idx);
                }
                i++;
        }

        TEST_ASSERT_MESSAGE(i == NUMBER, "Foreach_safe should cycle through whole list even if we are deleting nodes in the for");
        TEST_ASSERT_MESSAGE(root.next  == &test_list[1].node, "New 'head' should be the second element since we removed the first one");

        i = 0;

        ll_foreach_safe(&root, idx, idx_safe) {
                i++;
        }

        TEST_ASSERT_MESSAGE(i == NUMBER - 1, "We deleted an element, we should only go through the list one less time now");
}

void test_ll_indexof_paramCheck(void)
{
        struct ll_node root = { 0 };
        struct ll_node temp = { 0 };

        ll_init(&root);

        TEST_ASSERT(ll_indexof(NULL, NULL) == -1);
        TEST_ASSERT(ll_indexof(&root, NULL) == -1);
        TEST_ASSERT(ll_indexof(&root, &temp) == -1);

        /* set root */
        ll_append_node(&root, &temp);

        TEST_ASSERT(ll_indexof(&root, &temp) == 0);
}

void test_ll_count(void)
{
        struct ll_node root = { 0 };
        struct ll_node temp = { 0 }, temp1 = { 0 };

        ll_init(&root);

        TEST_ASSERT(0 == ll_count(NULL));
        TEST_ASSERT(0 == ll_count(&root));

        ll_append_node(&root, &temp);

        TEST_ASSERT(1 == ll_count(&root));

        ll_append_node(&root, &temp1);

        TEST_ASSERT(2 == ll_count(&root));
}

void test_ll_is_linked(void)
{
        struct ll_node root = { 0 };
        struct ll_node temp = { 0 }, temp1 = { 0 };

        ll_init(&root);

        TEST_ASSERT_FALSE(ll_is_linked(&root, &temp));
        TEST_ASSERT_FALSE(ll_is_linked(&root, &temp1));

        ll_append_node(&root, &temp);

        TEST_ASSERT(ll_is_linked(&root, &temp));
        TEST_ASSERT_FALSE(ll_is_linked(&root, &temp1));

        ll_append_node(&root, &temp1);

        TEST_ASSERT(ll_is_linked(&root, &temp));
        TEST_ASSERT(ll_is_linked(&root, &temp1));
}

void test_ll_is_empty(void)
{
        struct ll_node root = { 0 };
        struct ll_node temp = { 0 };

        ll_init(&root);

        TEST_ASSERT(ll_is_empty(&root));

        ll_append_node(&root, &temp);

        TEST_ASSERT_FALSE(ll_is_empty(&root));
}

void test_ll_is_tail(void)
{
        struct ll_node root = { 0 };
        struct ll_node temp = { 0 }, temp1 = { 0 };

        ll_init(&root);

        TEST_ASSERT_FALSE(ll_is_tail(&root, &temp));
        TEST_ASSERT_FALSE(ll_is_tail(&root, &temp1));

        ll_append_node(&root, &temp);

        TEST_ASSERT(ll_is_tail(&root, &temp));
        TEST_ASSERT_FALSE(ll_is_tail(&root, &temp1));

        ll_append_node(&root, &temp1);

        TEST_ASSERT_FALSE(ll_is_tail(&root, &temp));
        TEST_ASSERT(ll_is_tail(&root, &temp1));
}
