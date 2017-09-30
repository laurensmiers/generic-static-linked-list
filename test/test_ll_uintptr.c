#include "unity.h"
#include "ll_uintptr.h"
#include <stdlib.h>
#include <stddef.h>

#define NUMBER (4)

typedef struct {
  int a;
  uintptr_t next;
} ll_t;

static ll_t list[NUMBER];

void setUp(void)
{
  for(int i = 0; i < NUMBER; ++i) {
    list[i].next = 0;
    list[i].a = i+1;
  }
}

void tearDown(void)
{
}

static void link_array(ll_t **root) {
  for(int i = 0; i < NUMBER; ++i) {
    ll_add_node((uintptr_t *)root, (uintptr_t)&list[i], offsetof(ll_t, next));
  }
}

static void print_node(ll_t *l)
{
  printf("\n");  
  printf("NODE, address: %p\n", (uintptr_t)l);
  printf("next: %p\n", l->next);  
  printf("a: %d\n", l->a);
  printf("\n");
}

static void print_arr(void)
{
  for(int i = 0; i < NUMBER; ++i) {
    print_node(&list[i]);
  }
}

static void print(ll_t *root)
{
  ll_t *temp = NULL;

  temp = root;

  while (temp) {
    print_node(temp);
    temp = (ll_t *)temp->next;
  }
}

void test_ll_add_node_paramCheck(void)
{
  ll_t *root = NULL;

  list[0].next = 0;
  list[0].a = 100;
  
  TEST_ASSERT_MESSAGE(ll_add_node(NULL, (uintptr_t)&list[0], offsetof(ll_t, next)) == ll_status_Error,
		      "Passing NULL should result in error code (1)"
		      );

  TEST_ASSERT_MESSAGE(list[0].next == 0, "node should remain unaltered (1)");
  TEST_ASSERT_MESSAGE(list[0].a == 100, "node should remain unaltered (2)");

  TEST_ASSERT_MESSAGE(ll_add_node((uintptr_t *)&root, (uintptr_t)NULL, offsetof(ll_t, next)) == ll_status_Error,
		      "Passing NULL should result in error code (2)"
		      );

  TEST_ASSERT_MESSAGE(ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next)) == ll_status_OK,
		      "Passing valid args should result in success status code"
		      );
  
}

void test_ll_remove_node_paramCheck(void)
{
  ll_t *root = NULL;

  TEST_ASSERT_MESSAGE(ll_remove_node(NULL, (uintptr_t)&list[0], offsetof(ll_t, next)) == ll_status_Error,
		      "Passing NULL should result in error code (1)"
		      );
  TEST_ASSERT_MESSAGE(ll_remove_node((uintptr_t *)&root, (uintptr_t)NULL, offsetof(ll_t, next)) == ll_status_Error,
		      "Passing NULL should result in error code (2)"
		      );
  
  /* Passing valid args, this requires a valid linked list */
  link_array(&root);

  TEST_ASSERT_MESSAGE(ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[1], offsetof(ll_t, next)) == ll_status_OK,
  		      "Passing valid args should result in success status code"
  		      );
}

void test_ll_rootInit(void)
{
  ll_t *root = NULL;

  /**
   *  Some init values
   *  Fake a link by setting link to a value
   */
  list[0].a = 100;
  list[0].next = 0x12345;

  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));

  TEST_ASSERT_MESSAGE(root == &list[0], "root should be set");
  TEST_ASSERT_MESSAGE(root->next == 0, "root nextNode should be set to 0");
}

void test_ll_AddingOneElement(void)
{
  ll_t *root = NULL;

  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[1], offsetof(ll_t, next));

  TEST_ASSERT_MESSAGE(list[0].next == (uintptr_t)&list[1], "link should be present");
}

void test_ll_addingSameElement(void)
{
  ll_t *root = NULL;
  
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));

  TEST_ASSERT_MESSAGE(!list[0].next, "Adding same element should not be possible");
}

void test_ll_AddingSeveralNodes(void)
{
  ll_t *root = NULL;

  link_array(&root);  

  for(int i = 0; i < NUMBER - 1; ++i) {
    TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should be fully complete");
  }
}

void test_ll_SanityCheckWhenDoingBadRemove(void)
{
  ll_t *root = NULL;

  link_array(&root);

  ll_remove_node(NULL, (uintptr_t)&list[1], offsetof(ll_t, next));

  for(int i = 0; i < NUMBER - 1; ++i) {
    TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should still be fully complete");
  }
  
}

void test_ll_RemovingOneNode(void)
{
  ll_t *root = NULL;

  link_array(&root);
  
  ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[1], offsetof(ll_t, next));
  
  TEST_ASSERT_MESSAGE(list[0].next == (uintptr_t)&list[2], "removing node that is not root should NOT result in losing link");
  for(int i = 2; i < NUMBER - 1; ++i) {
    TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should still be there");
  }
}
  
void test_ll_RemovingRootNodeShouldResultInNewRoot(void)
{
  ll_t *root = NULL;

  link_array(&root);

  ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));
  
  TEST_ASSERT_MESSAGE(root == &list[1], "removing root should result in next node to be root");
  for(int i = 1; i < NUMBER - 1; ++i) {
    TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should still be there");
  }
}

void test_ll_removeRootAndAddItAgain(void)
{
  ll_t *root = NULL;

  link_array(&root);

  printf("------------\n");
  print(root);
  printf("------------\n");

  printf("------------\n");
  printf("remove root...\n");
  ll_remove_node((uintptr_t *)&root, (uintptr_t)root, offsetof(ll_t, next));
  print(root);
  printf("------------\n");

  printf("------------\n");
  printf("remove list[2]...\n");
  ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[2], offsetof(ll_t, next));
  print(root);
  printf("------------\n");

  printf("------------\n");
  printf("add list[0]...\n");
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));
  print(root);
  printf("------------\n");
}

void test_ll_removeNodendAddItAgain(void)
{
  ll_t *root = NULL;

  link_array(&root);

  printf("------------\n");
  print(root);
  printf("------------\n");

  printf("------------\n");
  printf("remove node...\n");
  ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[2], offsetof(ll_t, next));
  print(root);
  printf("------------\n");

  printf("------------\n");
  printf("add node...\n");
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[2], offsetof(ll_t, next));
  print(root);
  printf("------------\n");
}



