#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

extern "C" {
#include "queue.h"
}

#define EXPECT_CRASH(statement) EXPECT_EXIT((statement,exit(0)),::testing::KilledBySignal(SIGSEGV),".*")
#define EXPECT_NO_CRASH(statement) EXPECT_EXIT((statement,exit(0)),::testing::ExitedWithCode(0),".*")

#define MYTYPE int
void myfree(gpointer p) { free(p); }

class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
    q = queue_init(myfree); // queue_init(NULL);
    for (int i=0;i<100;i++) {
      tab[i]=(MYTYPE *)malloc(sizeof(MYTYPE));
      *(tab[i])=(MYTYPE)i;
    }
  }
  void TearDown() override { EXPECT_NO_CRASH(queue_free(q)); }
  queue_t* q;
  MYTYPE* tab[100];
};

/* ********** TEST INIT & FREE ********** */

TEST_F(QueueTest, Init_Free) { EXPECT_FALSE(NULL == q); }

/* ********** TEST PUSH ********** */

TEST_F(QueueTest, Push) {
  for (int i = 0; i < 100; i++) {
    queue_push_head(q, tab[i]);
    MYTYPE* ptr_head = (MYTYPE*) queue_peek_head(q);
    EXPECT_EQ(*ptr_head, (MYTYPE)i);
    MYTYPE* ptr_tail = (MYTYPE*) queue_peek_tail(q);
    EXPECT_EQ(*ptr_tail, (MYTYPE)0);
  }
}

/* ********** TEST POP ********** */

TEST_F(QueueTest, Pop) {
  for (int i = 0; i < 100; i++) queue_push_head(q, tab[i]);
  for (int i = 0; i < 100; i++) {
    MYTYPE* ptr_v = (MYTYPE*) queue_pop_tail(q);
    EXPECT_EQ(*ptr_v, (MYTYPE)i);
    myfree(ptr_v);
  }
}

/* ********** TEST DROP ********** */

TEST_F(QueueTest, Drop) {
  for (int i = 0; i < 100; i++) queue_push_head(q, tab[i]);
  for (int i = 0; i < 100; i++) queue_drop_tail(q);
  EXPECT_EQ(queue_length(q), 0);
}


/* ********** TEST EMPTY ********** */

TEST_F(QueueTest, Length) {
  EXPECT_EQ(queue_length(q), 0);
  for (int i = 0; i < 10; i++) queue_push_head(q, tab[i]);
  EXPECT_EQ(queue_length(q), 10);
  for (int i = 0; i < 10; i++) myfree(queue_pop_tail(q));
  EXPECT_EQ(queue_length(q), 0);
}

/* ********** TEST LENGTH ********** */

TEST_F(QueueTest, Empty) {
  for (int i = 0; i < 10; i++) queue_push_head(q, tab[i]);
  EXPECT_FALSE(queue_is_empty(q));
  for (int i = 0; i < 10; i++) myfree(queue_pop_tail(q));
  EXPECT_TRUE(queue_is_empty(q));
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char **argv) {
  /* run google tests */
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
