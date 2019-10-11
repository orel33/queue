CFLAGS= -std=c99 -Wall

ALL: sample test_queue

# dependencies
sample: sample.o queue.o
test_queue: test_queue.o queue.o
queue.o: queue.c queue.h
sample.o: sample.c queue.h
test_queue.o: test_queue.c queue.h

.PHONY: clean test

test: test_queue
	./test_queue test0
	./test_queue test1
	./test_queue test2

clean:
	rm -f *.o sample test_queue