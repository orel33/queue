#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "queue.h"

/* *********************************************************** */

struct queue_s {
    struct element_s *head;
    struct element_s *tail;
    unsigned int      length;
    gfree_function    free_func;
};

/* *********************************************************** */

struct element_s {
    gpointer          value;
    struct element_s *next;
    struct element_s *prev;
};

/* *********************************************************** */

typedef struct queue_s   queue_t;
typedef struct element_s element_t;

/* *********************************************************** */

queue_t *
queue_init( gfree_function f )
{
    queue_t *q = malloc( sizeof( queue_t ) );
    assert( q );
    q->length = 0;
    q->tail = q->head = NULL;
    q->free_func      = f;
    return q;
}

/* *********************************************************** */

void
queue_push_head( queue_t *q, gpointer v )
{
    assert( q );
    element_t *e = malloc( sizeof( element_t ) );
    assert( e );
    e->value = v;
    e->prev  = NULL;
    e->next  = q->head;
    if ( q->head )
        q->head->prev = e;
    q->head = e;
    if ( !q->tail )
        q->tail = e;
    q->length++;
}

/* *********************************************************** */

gpointer
queue_pop_tail( queue_t *q )
{
    assert( q );
    assert( q->length > 0 );
    assert( q->tail );
    gpointer   v    = q->tail->value;
    element_t *prev = q->tail->prev;
    if ( prev )
        prev->next = NULL;
    free( q->tail );
    q->tail = prev;
    q->length--;
    if ( !q->tail )
        q->head = NULL;
    return v;
}

/* *********************************************************** */

void
queue_drop_tail( queue_t *q )
{
    assert( q );
    assert( q->length > 0 );
    assert( q->tail );
    element_t *prev = q->tail->prev;
    if ( prev )
        prev->next = NULL;
    if ( q->free_func != NULL )
        q->free_func( q->tail->value );
    free( q->tail );
    q->tail = prev;
    q->length--;
    if ( !q->tail )
        q->head = NULL;
}

/* *********************************************************** */

int
queue_length( const queue_t *q )
{
    assert( q );
    return q->length;
}

/* *********************************************************** */

bool
queue_is_empty( const queue_t *q )
{
    assert( q );
    return ( q->length == 0 );
}

/* *********************************************************** */

gpointer
queue_peek_head( queue_t *q )
{
    assert( q );
    assert( q->head );
    return q->head->value;
}

/* *********************************************************** */

gpointer
queue_peek_tail( queue_t *q )
{
    assert( q );
    assert( q->tail );
    return q->tail->value;
}

/* *********************************************************** */

void
queue_free( queue_t *q )
{
    assert( q );
    element_t *e = q->head;
    while ( e ) {
        element_t *tmp = e;
        e              = e->next;
        if ( q->free_func != NULL )
            q->free_func( tmp->value );
        free( tmp );
    }
    free( q );
}

/* *********************************************************** */
