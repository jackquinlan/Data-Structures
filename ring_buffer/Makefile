.PHONY: all test clean

CC=gcc
CFLAGS=-std=gnu99 -Wall -pedantic -Werror

all: rbuf_test

ring.o: rbuf.c rbuf.h
	$(CC) $(CFLAGS) -c rbuf.c

rbuf_test: rbuf.o rbuf_test.c
	$(CC) $(CFLAGS) -o rbuf_test rbuf_test.c rbuf.o

test: rbuf_test
	./rbuf_test

clean:
	rm -f *.o
	rm -f rbuf_test
