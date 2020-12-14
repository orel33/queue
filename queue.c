#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "queue.h"

/* *********************************************************** */

struct queue_s
{
  struct element_s *head;
  struct element_s *tail;
  unsigned int length;
};

/* *********************************************************** */

struct element_s
{
  int value;
  struct element_s *next;
  struct element_s *prev;
};

/* *********************************************************** */

typedef struct queue_s queue_t;
typedef struct element_s element_t;

/* *********************************************************** */

queue_t *queue_init()
{
  queue_t *q = malloc(sizeof(queue_t));
  assert(q);
  q->length = 0;
  q->tail = q->head = NULL;
  return q;
}

/* *********************************************************** */

void queue_push_head(queue_t *q, int v)
{
  assert(q);
  element_t *e = malloc(sizeof(element_t));
  assert(e);
  e->value = v;
  e->prev = NULL;
  e->next = q->head;
  if (q->head)
    q->head->prev = e;
  q->head = e;
  if (!q->tail)
    q->tail = e;
  q->length++;
}

/* *********************************************************** */

void queue_push_tail(queue_t *q, int v)
{
  assert(q);
  element_t *e = malloc(sizeof(element_t));
  assert(e);
  e->value = v;
  e->prev = q->tail;
  e->next = NULL;
  if (q->tail)
    q->tail->next = e;
  q->tail = e;
  if (!q->head)
    q->head = e;
  q->length++;
}

/* *********************************************************** */

int queue_pop_head(queue_t *q)
{
  assert(q);
  assert(q->length > 0);
  assert(q->head);
  int v = q->head->value;
  element_t *next = q->head->next;
  if (next)
    next->prev = NULL;
  free(q->head);
  q->head = next;
  q->length--;
  if (!q->head)
    q->tail = NULL; // empty list
  return v;
}

/* *********************************************************** */

int queue_pop_tail(queue_t *q)
{
  assert(q);
  assert(q->length > 0);
  assert(q->tail);
  int v = q->tail->value;
  element_t *prev = q->tail->prev;
  if (prev)
    prev->next = NULL;
  free(q->tail);
  q->tail = prev;
  q->length--;
  if (!q->tail)
    q->head = NULL; // empty list
  return v;
}

/* *********************************************************** */

int queue_length(const queue_t *q)
{
  assert(q);
  return q->length;
}

/* *********************************************************** */

bool queue_is_empty(const queue_t *q)
{
  assert(q);
  return (q->length == 0);
}

/* *********************************************************** */

int queue_peek_head(queue_t *q)
{
  assert(q);
  assert(q->head);
  return q->head->value;
}

/* *********************************************************** */

int queue_peek_tail(queue_t *q)
{
  assert(q);
  assert(q->tail);
  return q->tail->value;
}

/* *********************************************************** */

void queue_free(queue_t *q)
{
  assert(q);
  element_t *e = q->head;
  while (e)
  {
    element_t *tmp = e;
    e = e->next;
    free(tmp);
  }
  free(q);
}

/* *********************************************************** */

void queue_clear(queue_t *q)
{
  assert(q);
  element_t *e = q->head;
  while (e)
  {
    element_t *tmp = e;
    e = e->next;
    free(tmp);
  }
  q->head = q->tail = NULL;
  assert(q->length == 0);
}

/* *********************************************************** */
