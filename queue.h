/**
 * @author aurelien.esnard@u-bordeaux.fr
 * @brief Lightweight implementation of double-ended queue data structure
 * following GLib interface.
 * @details For futher details, please visit :
 * https://developer.gnome.org/glib/stable/glib-Double-ended-Queues.html
 **/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

//@{

typedef struct queue_s queue_t;

/** Creates a new queue.*/
queue_t *queue_init();

/** Adds a new element at the head of the queue. */
void queue_push_head(queue_t *q, void *data);

/* Adds a new element at the tail of the queue. */
void queue_push_tail(queue_t *q, void *data);

/* Removes the first element of the queue and returns its data (or NULL if the
queue is empty). The returned element must be freed manually if it was
dynamically allocated.*/
void *queue_pop_head(queue_t *q);

/* Removes the last element of the queue and returns its data (or NULL if the
queue is empty). The returned element must be freed manually if it was
dynamically allocated. */
void *queue_pop_tail(queue_t *q);

/** Returns the number of elements in queue. */
int queue_length(const queue_t *q);

/** Returns true if the queue is empty. */
bool queue_is_empty(const queue_t *q);

/** Returns the first element of the queue. */
void *queue_peek_head(queue_t *q);

/** Returns the last element of the queue. */
void *queue_peek_tail(queue_t *q);

/** Removes all the elements in queue. If queue elements contain
 * dynamically-allocated memory, they should be freed first. */
void queue_clear(queue_t *q);

/** Convenience method, which frees all the memory used by a queue, and calls
 * the provided destroy function on each element in the queue. */
void queue_clear_full(queue_t *q, void (*destroy)(void *));

/** Frees the memory allocated for the queue. If queue elements contain
dynamically-allocated memory, you should either use queue_free_full() or free
them manually first. */
void queue_free(queue_t *q);

/** Convenience method, which frees all the memory used by a queue, and calls
the provided destroy function on every element's data. */
void queue_free_full(queue_t *q, void (*destroy)(void *));

//@}

#endif
