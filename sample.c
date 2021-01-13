#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define N 10

int main(void)
{
  assert(N > 3);

  // queue new
  printf("queue new\n");
  queue *q = queue_new();

  // N push
  for (int i = 0; i < N; i++)
  {
    printf("queue push head: %d \n", i);
    int *data = (int *)malloc(sizeof(int));
    assert(data);
    *data = i;
    queue_push_head(q, data);
  }
  printf("queue length: %d\n", queue_length(q));

  int *head = (int *)queue_peek_head(q);
  printf("queue peek head: %d\n", *head);

  int *tail = (int *)queue_peek_tail(q);
  printf("queue peek tail: %d\n", *tail);

  // 1 first pop
  int *data = (int *)queue_pop_tail(q);
  printf("queue pop tail: %d\n", *data);
  free(data);
  printf("queue length: %d\n", queue_length(q));

  // N-3 pop
  for (int i = 0; i < N - 3; i++)
  {
    int *data = (int *)queue_pop_tail(q);
    printf("queue pop tail: %d\n", *data);
    free(data);
  }
  printf("queue length: %d\n", queue_length(q));

  // clear (2 last pop)
  printf("queue clear full\n");
  queue_clear_full(q, free);
  printf("queue length: %d\n", queue_length(q));

  // free
  printf("queue free\n");
  queue_free(q);
  q = NULL;

  return EXIT_SUCCESS;
}