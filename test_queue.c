#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* ********** TEST INIT & FREE ********** */

bool test_init_free(void)
{
  queue_t *q = queue_init();
  assert(q);
  queue_free(q);
  return true;
}

/* ********** TEST PUSH HEAD ********** */

bool test_push_head(int k)
{
  queue_t *q = queue_init();
  assert(q);

  for (int i = 0; i < k; i++)
  {
    queue_push_head(q, i);
    int head = queue_peek_head(q);
    assert(head == i);
    int tail = queue_peek_tail(q);
    assert(tail == 0);
  }

  queue_free(q);
  return true;
}

/* ********** TEST PUSH TAIL ********** */

bool test_push_tail(int k)
{
  return true;
}

/* ********** TEST POP HEAD ********** */

bool test_pop_head(int k)
{
  return true;
}

/* ********** TEST POP TAIL ********** */

bool test_pop_tail(int k)
{
  queue_t *q = queue_init();
  assert(q);
  for (int i = 0; i < k; i++)
    queue_push_head(q, i);

  for (int i = 0; i < k; i++)
  {
    int v = queue_pop_tail(q);
    assert(v == i);
  }
  queue_free(q);
  return true;
}

/* ********** TEST CLEAR ********** */

bool test_clear(int k)
{
  queue_t *q = queue_init();
  assert(q);
  for (int i = 0; i < k; i++)
    queue_push_head(q, i);
  assert(queue_length(q) == k);
  queue_clear(q);
  assert(queue_length(q) == 0);
  assert(queue_is_empty(q));
  queue_free(q);
  return true;
}

/* ********** TEST EMPTY ********** */

bool test_empty(int k)
{
  queue_t *q = queue_init();
  assert(q);
  assert(queue_is_empty(q));
  for (int i = 0; i < k; i++)
    queue_push_head(q, i);
  assert(!queue_is_empty(q));
  for (int i = 0; i < k; i++)
    queue_pop_tail(q);
  assert(queue_is_empty(q));
  queue_free(q);
  return true;
}

/* ********** TEST LENGTH ********** */

bool test_length(int k)
{
  queue_t *q = queue_init();
  assert(q);
  assert(queue_length(q) == 0);
  for (int i = 0; i < k; i++)
    queue_push_head(q, i);
  assert(queue_length(q) == k);
  queue_push_head(q, k);
  assert(queue_length(q) == (k + 1));
  queue_pop_tail(q);
  assert(queue_length(q) == k);
  for (int i = 0; i < k; i++)
    queue_pop_tail(q);
  assert(queue_length(q) == 0);
  queue_free(q);
  return true;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[])
{
  if (argc == 1)
    usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("init_free", argv[1]) == 0)
    ok = test_init_free();
  else if (strcmp("push_head", argv[1]) == 0)
    ok = test_push_head(100);
  else if (strcmp("pop_head", argv[1]) == 0)
    ok = test_pop_head(100);
  else if (strcmp("push_tail", argv[1]) == 0)
    ok = test_push_tail(100);
  else if (strcmp("pop_tail", argv[1]) == 0)
    ok = test_pop_tail(100);
  else if (strcmp("length", argv[1]) == 0)
    ok = test_length(10);
  else if (strcmp("empty", argv[1]) == 0)
    ok = test_empty(10);
  else if (strcmp("clear", argv[1]) == 0)
    ok = test_clear(10);
  else
  {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // print test result
  if (ok)
  {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  }
  else
  {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}
