#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define GTEST_HAS_PTHREAD 0
#define GTEST_BREAK_ON_FAILURE 0
#define GTEST_CATCH_EXCEPTIONS 1
#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"

extern "C" {
#include "queue.h"
}

# define EXPECT_CRASH(statement) EXPECT_EXIT((statement,exit(0)),::testing::KilledBySignal(SIGSEGV),".*")
# define EXPECT_NO_CRASH(statement) EXPECT_EXIT((statement,exit(0)),::testing::ExitedWithCode(0),".*")

class QueueTest : public ::testing::Test {
 protected:
  //QueueTest() { q = queue_init(); }
  //virtual ~QueueTest() { EXPECT_NO_CRASH(queue_free(q)); }
  void SetUp() override { q = queue_init(); } // should protect also queue_init ...
  void TearDown() override { EXPECT_NO_CRASH(queue_free(q)); }
  queue_t *q;
};

/* ********** TEST INIT & FREE ********** */

TEST_F(QueueTest, Init_Free) { EXPECT_FALSE(NULL == q); }

/* ********** TEST PUSH ********** */

TEST_F(QueueTest, Push) {
  for (int i = 0; i < 100; i++) {
    queue_push_head(q, i);
    int head = queue_peek_head(q);
    EXPECT_EQ(head, i);
    int tail = queue_peek_tail(q);
    EXPECT_EQ(tail, 0);
  }
}

/* ********** TEST POP ********** */

TEST_F(QueueTest, Pop) {
  for (int i = 0; i < 100; i++) queue_push_head(q, i);
  for (int i = 0; i < 100; i++) {
    int v = queue_pop_tail(q);
    EXPECT_EQ(v, i);
  }
}

/* ********** TEST EMPTY ********** */

TEST_F(QueueTest, Length) {
  EXPECT_EQ(queue_length(q), 0);
  for (int i = 0; i < 10; i++) queue_push_head(q, i);
  EXPECT_EQ(queue_length(q), 10);
  for (int i = 0; i < 10; i++) queue_pop_tail(q);
  EXPECT_EQ(queue_length(q), 0);
}

/* ********** TEST LENGTH ********** */

TEST_F(QueueTest, Empty) {
  for (int i = 0; i < 10; i++) queue_push_head(q, i);
  EXPECT_FALSE(queue_is_empty(q));
  for (int i = 0; i < 10; i++) queue_pop_tail(q);
  EXPECT_TRUE(queue_is_empty(q));
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char **argv) {
  /* run google tests */
  ::testing::InitGoogleTest(&argc, argv);
  //::testing::FLAGS_gtest_death_test_style="threadsafe";
  return RUN_ALL_TESTS();
}
