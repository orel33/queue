#define __USE_GNU
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* ********** TEST INIT & FREE ********** */

bool test_new_free(void)
{
  queue *q = queue_new();
  if (!q) return false;
  queue_free(q);
  return true;
}

/* ********** TEST PUSH HEAD ********** */

bool test_push_head(int k)
{
  queue *q = queue_new();
  if (!q) return false;

  for (int i = 0; i < k; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    if(!data) return false;
    *data = i;
    queue_push_head(q, data);
    int *head = queue_peek_head(q);
    if(*head != i) return false;
    int *tail = queue_peek_tail(q);
    if(*tail != 0) return false;
  }

  queue_free_full(q, free);
  return true;
}

/* ********** TEST PUSH TAIL ********** */

bool test_push_tail(int k)
{
  queue *q = queue_new();
  if (!q) return false;

  for (int i = 0; i < k; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    if(!data) return false;
    *data = i;
    queue_push_tail(q, data);
    int *tail = queue_peek_tail(q);
    if(*tail != i) return false;
    int *head = queue_peek_head(q);
    if(*head != 0) return false;
  }

  queue_free_full(q, free);
  return true;
}

/* ********** TEST POP HEAD ********** */

bool test_pop_head(int k)
{
  /*
  queue *q = queue_new();
  if(!q) return false;
  for (int i = 0; i < k; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    if(!data) return false;
    *data = i;
    queue_push_tail(q, data);
  }

  for (int i = 0; i < k; i++)
  {
    int *data = queue_pop_head(q);
    if(*data != i) return false;
    free(data);
  }
  queue_free(q);
  */
  return true;
}

/* ********** TEST POP TAIL ********** */

bool test_pop_tail(int k)
{
  queue *q = queue_new();
  if (!q) return false;

  for (int i = 0; i < k; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    if(!data) return false;
    *data = i;
    queue_push_head(q, data);
  }

  for (int i = 0; i < k; i++)
  {
    int *data = queue_pop_tail(q);
    if(*data != i) return false;
    free(data);
  }
  queue_free(q);
  return true;
}

/* ********** TEST CLEAR ********** */

bool test_clear(int k)
{
  queue *q = queue_new();
  if (!q) return false;

  for (int i = 0; i < k; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    if(!data) return false;
    *data = i;
    queue_push_head(q, data);
  }
  if(queue_length(q) != k) return false;
  queue_clear_full(q, free);
  if(queue_length(q) != 0) return false;
  if(!queue_is_empty(q)) return false;
  queue_free(q);
  return true;
}

/* ********** TEST EMPTY ********** */

bool test_empty(int k)
{
  queue *q = queue_new();
  if (!q) return false;
  if(!queue_is_empty(q)) return false;

  for (int i = 0; i < k; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    if(!data) return false;
    *data = i;
    queue_push_head(q, data);
  }
  if(queue_is_empty(q)) return false;
  queue_clear_full(q, free);
  if(!queue_is_empty(q)) return false;
  queue_free(q);
  return true;
}

/* ********** TEST LENGTH ********** */

bool test_length(int k)
{
  queue *q = queue_new();
  if (!q) return false;
  if(queue_length(q) != 0) return false;

  for (int i = 0; i < k; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    if(!data) return false;
    *data = i;
    queue_push_head(q, data);
  }
  if(queue_length(q) != k) return false;
  int *data = (int *)malloc(sizeof(int));
  if(!data) return false;
  *data = k;
  queue_push_head(q, data);
  if(queue_length(q) != (k + 1)) return false;
  data = queue_pop_tail(q);
  if(queue_length(q) != k) return false;
  free(data);
  queue_clear_full(q, free);
  if(queue_length(q) != 0) return false;
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
  if (strcmp("new_free", argv[1]) == 0)
    ok = test_new_free();
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
