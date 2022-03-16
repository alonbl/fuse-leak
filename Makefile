FUSE3_CFLAGS = $(shell pkg-config fuse3 --cflags)
FUSE3_LIBS = $(shell pkg-config fuse3 --libs)
CC = gcc
CFLAGS =
LDFLAGS =

all:	fuse-leak

clean:
	rm -f fuse-leak

fuse-leak:	fuse-leak.c
	$(CC) $(CFLAGS) -o $@ $< $(FUSE3_CFLAGS) $(FUSE3_LIBS) $(LDFLAGS)

check:	all
	./fuse-leak-test
