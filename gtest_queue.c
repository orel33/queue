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
  if (q == NULL) {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }
  queue_free(q);
  return true;
}

/* ********** TEST PUSH ********** */

bool test_push(int k) {
  queue_t *q = queue_init();
  if (q == NULL) {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }

  for (int i = 0; i < k; i++) {
    queue_push_head(q, i);
    int head = queue_peek_head(q);
    if (head != i) {
      fprintf(stderr, "Error: invalid queue head!\n");
      queue_free(q);
      return false;
    }
    int tail = queue_peek_tail(q);
    if (tail != 0) {
      fprintf(stderr, "Error: invalid queue tail!\n");
      queue_free(q);
      return false;
    }
  }

  queue_free(q);
  return true;
}

/* ********** TEST POP ********** */

bool test_pop(int k) {
  queue_t *q = queue_init();
  if (q == NULL) {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }
  for (int i = 0; i < k; i++) queue_push_head(q, i);

  for (int i = 0; i < k; i++) {
    int v = queue_pop_tail(q);
    if (v != i) {
      fprintf(stderr, "Error: invalid queue tail!\n");
      queue_free(q);
      return false;
    }
  }
  queue_free(q);
  return true;
}

/* ********** TEST EMPTY ********** */

bool test_empty(int k) {
  queue_t *q = queue_init();
  if (q == NULL) {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }

  if (!queue_is_empty(q)) {
    fprintf(stderr, "Error: queue not empty!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++) queue_push_head(q, i);

  if (queue_is_empty(q)) {
    fprintf(stderr, "Error: queue empty!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++) queue_pop_tail(q);

  if (!queue_is_empty(q)) {
    fprintf(stderr, "Error: queue not empty!\n");
    queue_free(q);
    return false;
  }

  queue_free(q);
  return true;
}

/* ********** TEST LENGTH ********** */

bool test_length(int k) {
  queue_t *q = queue_init();
  if (q == NULL) {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }

  if (queue_length(q) != 0) {
    fprintf(stderr, "Error: invalid queue length!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++) queue_push_head(q, i);

  if (queue_length(q) != k) {
    fprintf(stderr, "Error: invalid queue length!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++) queue_pop_tail(q);

  if (queue_length(q) != 0) {
    fprintf(stderr, "Error: invalid queue length!\n");
    queue_free(q);
    return false;
  }

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
