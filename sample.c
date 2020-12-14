#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define N 5

int main(void)
{
  queue *q = queue_init();
  printf("queue init\n");

  for (int i = 0; i < N; i++)
  {
    int *data = (int *)malloc(sizeof(int));
    assert(data);
    *data = i;
    queue_push_head(q, data);
    printf("queue push head: %d \n", i);
  }
  printf("queue length: %d \n", queue_length(q));

  int *head = (int *)queue_peek_head(q);
  printf("queue peek head: %d \n", *head);

  int *tail = (int *)queue_peek_tail(q);
  printf("queue peek tail: %d \n", *tail);

  printf("queue length: %d \n", queue_length(q));
  while (!queue_is_empty(q))
  {
    int *data = (int *)queue_pop_tail(q);
    printf("queue pop tail: %d \n", *data);
    free(data);
  }
  printf("queue length: %d \n", queue_length(q));

  queue_free(q);
  q = NULL;
  printf("queue free\n");

  return EXIT_SUCCESS;
}