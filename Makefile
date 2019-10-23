CFLAGS= -std=c11 -Wall -Wextra -pedantic -g
LDFLAGS=

ALL: googletest sample test_queue gtest_queue

# dependencies
sample: sample.o queue.o
queue.o: queue.c queue.h
sample.o: sample.c queue.h
test_queue: test_queue.o queue.o
test_queue.o: test_queue.c queue.h

gtest_queue: gtest_queue.o queue.o
	g++ -std=c++11 -fsanitize=address -L./googletest/build/lib -lgtest gtest_queue.o queue.o -o gtest_queue
gtest_queue.o: gtest_queue.cpp queue.h
	g++ -std=c++11 -fsanitize=address -I./googletest/googletest/include -g -c gtest_queue.cpp

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
