cmake_minimum_required(VERSION 3.0)

project("queue" C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall --coverage")

add_library(queue queue.c)
add_executable(sample sample.c)
target_link_libraries(sample queue)
add_executable(test_queue test_queue.c)
target_link_libraries(test_queue queue)

add_test(test_queue_new_free ./test_queue init_free)
add_test(test_queue_push_head ./test_queue push_head)
add_test(test_queue_pop_head ./test_queue pop_head)
add_test(test_queue_push_tail ./test_queue push_tail)
add_test(test_queue_pop_tail ./test_queue pop_tail)
add_test(test_queue_length ./test_queue length)
add_test(test_queue_empty ./test_queue empty)
add_test(test_queue_clear ./test_queue clear)

