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

typedef void* gpointer;
typedef const void *gconstpointer;
void (*gfree_function) (gpointer data);

/* *********************************************************** */
/*                          QUEUE                              */
/* *********************************************************** */

typedef struct queue_s queue_t;

queue_t* queue_init();
void queue_push_head(queue_t* q, gpointer v);
gpointer queue_pop_tail(queue_t* q);
int queue_length(const queue_t* q);
bool queue_is_empty(const queue_t* q);
gpointer queue_peek_head(queue_t* q);
gpointer queue_peek_tail(queue_t* q);
void queue_free(queue_t* q);

//@}

#endif
