#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

extern "C" {
#include "queue.h"
}

typedef int mytype_t;

void
myfree( gpointer p )
{
    free( p );
}

/* ********** TEST INIT & FREE ********** */

TEST( QueueTest, Init_Free )
{
    queue_t *q = queue_init( myfree );
    EXPECT_FALSE( NULL == q );
    queue_free( q );
}

/* ********** TEST PUSH ********** */

TEST( QueueTest, Push )
{
    queue_t *q = queue_init( myfree );
    for ( int i = 0; i < 100; i++ ) {
        mytype_t *ptr_in = (mytype_t *)malloc( sizeof( mytype_t ) );
        *ptr_in          = i;
        queue_push_head( q, ptr_in );
        mytype_t *ptr_head = (mytype_t *)queue_peek_head( q );
        EXPECT_EQ( *ptr_head, (mytype_t)i );
        mytype_t *ptr_tail = (mytype_t *)queue_peek_tail( q );
        EXPECT_EQ( *ptr_tail, (mytype_t)0 );
    }
    queue_free( q );
}

/* ********** TEST POP ********** */

TEST( QueueTest, Pop )
{
    queue_t *q = queue_init( myfree );
    for ( int i = 0; i < 100; i++ ) {
        mytype_t *ptr_in = (mytype_t *)malloc( sizeof( mytype_t ) );
        *ptr_in          = i;
        queue_push_head( q, ptr_in );
    }
    for ( int i = 0; i < 100; i++ ) {
        mytype_t *ptr_out = (mytype_t *)queue_pop_tail( q );
        EXPECT_EQ( *ptr_out, (mytype_t)i );
        myfree( ptr_out );
    }
    queue_free( q );
}

/* ********** TEST DROP ********** */

TEST( QueueTest, Drop )
{
    queue_t *q = queue_init( myfree );
    for ( int i = 0; i < 100; i++ ) {
        mytype_t *ptr_in = (mytype_t *)malloc( sizeof( mytype_t ) );
        *ptr_in          = i;
        queue_push_head( q, ptr_in );
    }
    for ( int i = 0; i < 100; i++ )
        queue_drop_tail( q );
    EXPECT_EQ( queue_length( q ), 0 );
    queue_free( q );
}

/* ********** TEST EMPTY ********** */

TEST( QueueTest, Length )
{
    queue_t *q = queue_init( myfree );
    EXPECT_EQ( queue_length( q ), 0 );
    for ( int i = 0; i < 10; i++ ) {
        mytype_t *ptr_in = (mytype_t *)malloc( sizeof( mytype_t ) );
        *ptr_in          = i;
        queue_push_head( q, ptr_in );
    }
    EXPECT_EQ( queue_length( q ), 10 );
    for ( int i = 0; i < 10; i++ )
        queue_drop_tail( q );
    EXPECT_EQ( queue_length( q ), 0 );
    queue_free( q );
}

/* ********** TEST LENGTH ********** */

TEST( QueueTest, Empty )
{
    queue_t *q = queue_init( myfree );
    for ( int i = 0; i < 10; i++ ) {
        mytype_t *ptr_in = (mytype_t *)malloc( sizeof( mytype_t ) );
        *ptr_in          = i;
        queue_push_head( q, ptr_in );
    }
    EXPECT_FALSE( queue_is_empty( q ) );
    for ( int i = 0; i < 10; i++ )
        queue_drop_tail( q );
    EXPECT_TRUE( queue_is_empty( q ) );
    queue_free( q );
}

/* ********** MAIN ROUTINE ********** */

int
main( int argc, char **argv )
{
    /* run google tests */
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
