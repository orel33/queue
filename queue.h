/**
 * @file queue.h
 * @author aurelien.esnard@u-bordeaux.fr
 * @brief Lightweight implementation of double-ended queue data structure
 * following GLib interface.
 * @details For further details, please visit :
 * https://developer.gnome.org/glib/stable/glib-Double-ended-Queues.html
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/**
 * @defgroup Queue Queue
 * @{
 */

/**
 * @brief Opaque structure representing a queue.
 */
typedef struct queue_s queue;

/**
 * @brief Creates a new queue.
 * @return A pointer to the newly created queue.
 */
queue *queue_new();

/**
 * @brief Adds a new element at the head of the queue.
 * @param q Pointer to the queue.
 * @param data Pointer to the data to be added.
 */
void queue_push_head(queue *q, void *data);

/**
 * @brief Adds a new element at the tail of the queue.
 * @param q Pointer to the queue.
 * @param data Pointer to the data to be added.
 */
void queue_push_tail(queue *q, void *data);

/**
 * @brief Removes the first element of the queue and returns its data.
 * @param q Pointer to the queue.
 * @return Pointer to the data of the removed element, or NULL if the queue is empty.
 * @note The returned element must be freed manually if it was dynamically allocated.
 */
void *queue_pop_head(queue *q);

/**
 * @brief Removes the last element of the queue and returns its data.
 * @param q Pointer to the queue.
 * @return Pointer to the data of the removed element, or NULL if the queue is empty.
 * @note The returned element must be freed manually if it was dynamically allocated.
 */
void *queue_pop_tail(queue *q);

/**
 * @brief Returns the number of elements in the queue.
 * @param q Pointer to the queue.
 * @return The number of elements in the queue.
 */
int queue_length(const queue *q);

/**
 * @brief Checks if the queue is empty.
 * @param q Pointer to the queue.
 * @return true if the queue is empty, false otherwise.
 */
bool queue_is_empty(const queue *q);

/**
 * @brief Returns the first element of the queue.
 * @param q Pointer to the queue.
 * @return Pointer to the data of the first element.
 */
void *queue_peek_head(queue *q);

/**
 * @brief Returns the last element of the queue.
 * @param q Pointer to the queue.
 * @return Pointer to the data of the last element.
 */
void *queue_peek_tail(queue *q);

/**
 * @brief Removes all the elements in the queue.
 * @param q Pointer to the queue.
 * @note If queue elements contain dynamically-allocated memory, they should be freed first.
 */
void queue_clear(queue *q);

/**
 * @brief Frees all the memory used by a queue, and calls the provided destroy function on each element in the queue.
 * @param q Pointer to the queue.
 * @param destroy Function pointer to the destroy function.
 */
void queue_clear_full(queue *q, void (*destroy)(void *));

/**
 * @brief Frees the memory allocated for the queue.
 * @param q Pointer to the queue.
 * @note If queue elements contain dynamically-allocated memory, you should either use queue_free_full() or free them manually first.
 */
void queue_free(queue *q);

/**
 * @brief Frees all the memory used by a queue, and calls the provided destroy function on every element's data.
 * @param q Pointer to the queue.
 * @param destroy Function pointer to the destroy function.
 */
void queue_free_full(queue *q, void (*destroy)(void *));

/** @} */

#endif /* QUEUE_H */