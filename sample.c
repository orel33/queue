#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define N 5

typedef int mytype_t;

void
myfree( gpointer p )
{
    free( p );
}

int
main( void )
{
    queue_t *q = queue_init( myfree );
    printf( "queue init\n" );

    for ( int i = 0; i < N; i++ ) {
        mytype_t *ptr_in = (mytype_t *)malloc( sizeof( mytype_t ) );
        *ptr_in          = i;
        queue_push_head( q, ptr_in );
        printf( "queue push head: %d \n", i );
    }
    printf( "queue length: %d \n", queue_length( q ) );

    mytype_t *ptr_head = (mytype_t *)queue_peek_head( q );
    printf( "queue peek head: %d \n", *ptr_head );

    mytype_t *ptr_tail = (mytype_t *)queue_peek_tail( q );
    printf( "queue peek tail: %d \n", *ptr_tail );

    printf( "queue length: %d \n", queue_length( q ) );
    while ( !queue_is_empty( q ) ) {
        mytype_t *ptr_v = (mytype_t *)queue_pop_tail( q );
        printf( "queue pop tail: %d \n", *ptr_v );
    }
    printf( "queue length: %d \n", queue_length( q ) );

    queue_free( q );
    q = NULL;
    printf( "queue free\n" );

    return EXIT_SUCCESS;
}
