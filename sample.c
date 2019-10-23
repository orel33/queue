#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define N 5

int main(void) {
  queue_t* q = queue_init();
  printf("queue init\n");

  for (int i = 0; i < N; i++) {
    queue_push_head(q, i);
    printf("queue push head: %d \n", i);
  }
  printf("queue length: %d \n", queue_length(q));

  int head = queue_peek_head(q);
  printf("queue peek head: %d \n", head);

  int tail = queue_peek_tail(q);
  printf("queue peek tail: %d \n", tail);

  printf("queue length: %d \n", queue_length(q));
  while (!queue_is_empty(q)) {
    int v = queue_pop_tail(q);
    printf("queue pop tail: %d \n", v);
  }
  printf("queue length: %d \n", queue_length(q));

  queue_free(q);
  q = NULL;
  printf("queue free\n");

  return EXIT_SUCCESS;
}

