cmake_minimum_required(VERSION 2.6)

project("queue" C)

enable_testing()

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99 -g")

add_executable(sample sample.c queue.c)
add_executable(test_queue test_queue.c queue.c)

add_test(test_queue_init_free ./test_queue init_free)
add_test(test_queue_push ./test_queue push)
add_test(test_queue_pop ./test_queue pop)
add_test(test_queue_length ./test_queue length)
add_test(test_queue_empty ./test_queue empty)

