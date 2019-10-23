#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

extern "C" {
  #include "queue.h"
}

/* ********** TEST INIT & FREE ********** */

bool test_init_free(void) {
  queue_t *q = queue_init();
  EXPECT_FALSE(NULL == q);
  queue_free(q);
  return true;
}

/* ********** TEST PUSH ********** */

bool test_push(int k) {
  queue_t *q = queue_init();
  EXPECT_FALSE(NULL == q);
  for (int i = 0; i < k; i++) {
    queue_push_head(q, i);
    int head = queue_peek_head(q);
    EXPECT_EQ(head, i);
    int tail = queue_peek_tail(q);
    EXPECT_EQ(tail, 0);
  }
  queue_free(q);
  return true;
}

/* ********** TEST POP ********** */

bool test_pop(int k) {
  queue_t *q = queue_init();
  EXPECT_FALSE(NULL == q);
  for (int i = 0; i < k; i++) queue_push_head(q, i);
  for (int i = 0; i < k; i++) {
    int v = queue_pop_tail(q);
    EXPECT_EQ(v, i);
  }
  queue_free(q);
  return true;
}

/* ********** TEST EMPTY ********** */

bool test_empty(int k) {
  queue_t *q = queue_init();
  EXPECT_FALSE(NULL == q);
  for (int i = 0; i < k; i++) queue_push_head(q, i);
  EXPECT_FALSE(queue_is_empty(q));
  for (int i = 0; i < k; i++) queue_pop_tail(q);
  EXPECT_TRUE(queue_is_empty(q));
  queue_free(q);
  return true;
}

/* ********** TEST LENGTH ********** */

bool test_length(int k) {
  queue_t *q = queue_init();
  EXPECT_FALSE(NULL == q);
  EXPECT_EQ(queue_length(q), 0);
  for (int i = 0; i < k; i++) queue_push_head(q, i);
  EXPECT_EQ(queue_length(q), k);
  for (int i = 0; i < k; i++) queue_pop_tail(q);
  EXPECT_EQ(queue_length(q), 0);
  queue_free(q);
  return true;
}

TEST(QueueTest, Init_Free)
{
  EXPECT_TRUE(test_init_free());
}

TEST(QueueTest, Push)
{
  EXPECT_TRUE(test_push(100));
}

TEST(QueueTest, Pop)
{
  EXPECT_TRUE(test_pop(100));
}

TEST(QueueTest, Length)
{
  EXPECT_TRUE(test_length(10));
}

TEST(QueueTest, Empty)
{
  EXPECT_TRUE(test_empty(10));
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char **argv)
{
  /* run google tests */
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
