cmake_minimum_required(VERSION 2.6)

project("queue" C)

include(CTest)
enable_testing()

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99 -g")

add_executable(sample sample.c queue.c)
add_executable(test_queue test_queue.c queue.c)

add_test(test_queue_new_free ./test_queue init_free)
add_test(test_queue_push_head ./test_queue push_head)
add_test(test_queue_pop_head ./test_queue pop_head)
add_test(test_queue_push_tail ./test_queue push_tail)
add_test(test_queue_pop_tail ./test_queue pop_tail)
add_test(test_queue_length ./test_queue length)
add_test(test_queue_empty ./test_queue empty)
add_test(test_queue_clear ./test_queue clear)

