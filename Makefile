CFLAGS= -std=c99 -Wall -fsanitize=address -g
LDFLAGS= -fsanitize=address

ALL: sample test_queue

# dependencies
sample: sample.o queue.o
test_queue: test_queue.o queue.o
queue.o: queue.c queue.h
sample.o: sample.c queue.h
test_queue.o: test_queue.c queue.h

.PHONY: clean test

test: test_queue
	@ ./test_queue init_free
	@ ./test_queue push
	@ ./test_queue pop
	@ ./test_queue length
	@ ./test_queue empty

clean:
	rm -f *.o sample test_queue