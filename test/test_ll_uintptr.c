#include "unity.h"
#include "ll_uintptr.h"
#include <stdlib.h>
#include <stddef.h>

#define NUMBER (4)

typedef struct {
  int a;
  uintptr_t next;
} ll_t;

ll_t list[NUMBER];

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

void test_ll_0(void)
{
  ll_t *root = NULL;

  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));

  TEST_ASSERT_MESSAGE(root == &list[0], "root should be set");
}

void test_ll_1(void)
{
  ll_t *root = NULL;

  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[1], offsetof(ll_t, next));

  TEST_ASSERT_MESSAGE(list[0].next == (uintptr_t)&list[1], "link should be present");
}

void test_ll_2(void)
{
  ll_t *root = NULL;
  
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));
  ll_add_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next));

  TEST_ASSERT_MESSAGE(!list[0].next, "Adding same element should not be possible");
}

void test_ll_3(void)
{
  ll_t *root = NULL;

  for(int i = 0; i < NUMBER; ++i) {
    ll_add_node((uintptr_t *)&root, (uintptr_t)&list[i], offsetof(ll_t, next));
  }

  for(int i = 0; i < NUMBER - 1; ++i) {
    TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should be fully complete");
  }
}

/* void test_ll_4(void) */
/* { */
/*   ll_t *root = NULL; */

/*   for(int i = 0; i < NUMBER; ++i) { */
/*     ll_add_node((uintptr_t *)&root, (uintptr_t)&list[i], offsetof(ll_t, next));     */
/*   } */

/*   ll_remove_node(NULL, (uintptr_t)&list[1], offsetof(ll_t, next)); */

/*   for(int i = 0; i < NUMBER - 1; ++i) { */
/*     TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should still be fully complete");   */
/*   } */
  
/* } */

/* void test_ll_5(void) */
/* { */
/*   ll_t *root = NULL; */

/*   for(int i = 0; i < NUMBER; ++i) { */
/*     ll_add_node((uintptr_t *)&root, (uintptr_t)&list[i], offsetof(ll_t, next)); */
/*   } */

/*   ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[1], offsetof(ll_t, next));   */

/*   TEST_ASSERT_MESSAGE(list[0].next == (uintptr_t)&list[2], "removing node that is not root should NOT result in losing link"); */
/*   for(int i = 2; i < NUMBER - 1; ++i) { */
/*     TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should still be there");   */
/*   } */

/* } */

/* void test_ll_6(void) */
/* { */
/*   ll_t *root = NULL; */

/*   for(int i = 0; i < NUMBER; ++i) { */
/*     ll_add_node((uintptr_t *)&root, (uintptr_t)&list[i], offsetof(ll_t, next)); */
/*   } */

/*   ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[1], offsetof(ll_t, next));   */

/*   TEST_ASSERT_MESSAGE(list[0].next == (uintptr_t)&list[2], "removing node that is not root should NOT result in losing link"); */
/*   for(int i = 2; i < NUMBER - 1; ++i) { */
/*     TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should still be there"); */
/*   } */
/* } */

/* void test_ll_7(void) */
/* { */
/*   ll_t *root = NULL; */

/*   for(int i = 0; i < NUMBER; ++i) { */
/*     ll_add_node((uintptr_t *)&root, (uintptr_t)&list[i], offsetof(ll_t, next)); */
/*   } */

/*   ll_remove_node((uintptr_t *)&root, (uintptr_t)&list[0], offsetof(ll_t, next)); */
  
/*   TEST_ASSERT_MESSAGE(root == &list[1], "removing root should result in next node to be root"); */
/*   for(int i = 1; i < NUMBER - 1; ++i) { */
/*     TEST_ASSERT_MESSAGE(list[i].next == (uintptr_t)&list[i+1], "link should still be there"); */
/*   } */
/* } */

/* void test_ll_print(void) */
/* { */
/*   ll_t *root = NULL; */

/*   for(int i = 0; i < NUMBER; ++i) { */
/*     ll_add_node((uintptr_t *)&root, (uintptr_t)&list[i], offsetof(ll_t, next)); */
/*   } */

/*   print(root); */

/*   printf("------------\n"); */
/*   printf("remove root...\n");   */
/*   ll_remove_node((uintptr_t *)&root, (uintptr_t)root, offsetof(ll_t, next)); */
/*   printf("------------\n"); */
/*   print(root);   */
/* } */



