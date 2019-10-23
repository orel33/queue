CFLAGS= -std=c++11 -Wall -Wextra -pedantic -g -fsanitize=address -I./googletest/googletest/include
LDFLAGS= -fsanitize=address -L./googletest/build/lib -lgtest
CC = g++ # need C++ for Google Test

ALL: googletest sample test_queue gtest_queue

# dependencies
sample: sample.o queue.o
queue.o: queue.c queue.h
sample.o: sample.c queue.h

test_queue: test_queue.o queue.o
test_queue.o: test_queue.c queue.h

gtest_queue: gtest_queue.o queue.o
gtest_queue.o: gtest_queue.c queue.h

.PHONY: clean test gtest

test: test_queue
	./test_queue init_free
	./test_queue push
	./test_queue pop
	./test_queue length
	./test_queue empty

gtest: gtest_queue
	./gtest_queue

googletest:
	(git clone git://github.com/google/googletest.git ; cd googletest ; mkdir build ; cd build ; cmake .. ; make)

clean:
	rm -f *.o sample test_queue gtest_queue
	rm -rf ./googletest
