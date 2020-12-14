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
  if (q == NULL)
  {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }
  queue_free(q);
  return true;
}

/* ********** TEST PUSH HEAD ********** */

bool test_push_head(int k)
{
  queue_t *q = queue_init();
  if (q == NULL)
  {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }

  for (int i = 0; i < k; i++)
  {
    queue_push_head(q, i);
    int head = queue_peek_head(q);
    if (head != i)
    {
      fprintf(stderr, "Error: invalid queue head!\n");
      queue_free(q);
      return false;
    }
    int tail = queue_peek_tail(q);
    if (tail != 0)
    {
      fprintf(stderr, "Error: invalid queue tail!\n");
      queue_free(q);
      return false;
    }
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
  if (q == NULL)
  {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }
  for (int i = 0; i < k; i++)
    queue_push_head(q, i);

  for (int i = 0; i < k; i++)
  {
    int v = queue_pop_tail(q);
    if (v != i)
    {
      fprintf(stderr, "Error: invalid queue tail!\n");
      queue_free(q);
      return false;
    }
  }
  queue_free(q);
  return true;
}

/* ********** TEST CLEAR ********** */

bool test_clear(int k)
{
  // TODO: todo
  return true;
}

/* ********** TEST EMPTY ********** */

bool test_empty(int k)
{
  queue_t *q = queue_init();
  if (q == NULL)
  {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }

  if (!queue_is_empty(q))
  {
    fprintf(stderr, "Error: queue not empty!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++)
    queue_push_head(q, i);

  if (queue_is_empty(q))
  {
    fprintf(stderr, "Error: queue empty!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++)
    queue_pop_tail(q);

  if (!queue_is_empty(q))
  {
    fprintf(stderr, "Error: queue not empty!\n");
    queue_free(q);
    return false;
  }

  queue_free(q);
  return true;
}

/* ********** TEST LENGTH ********** */

bool test_length(int k)
{
  queue_t *q = queue_init();
  if (q == NULL)
  {
    fprintf(stderr, "Error: invalid queue init!\n");
    return false;
  }

  if (queue_length(q) != 0)
  {
    fprintf(stderr, "Error: invalid queue length!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++)
    queue_push_head(q, i);

  if (queue_length(q) != k)
  {
    fprintf(stderr, "Error: invalid queue length!\n");
    queue_free(q);
    return false;
  }

  for (int i = 0; i < k; i++)
    queue_pop_tail(q);

  if (queue_length(q) != 0)
  {
    fprintf(stderr, "Error: invalid queue length!\n");
    queue_free(q);
    return false;
  }

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
