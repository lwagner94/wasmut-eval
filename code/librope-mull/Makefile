.PHONY: all clean

CC=clang-12
CFLAGS=-O0 -Wall -I. -std=c99  -fexperimental-new-pass-manager -fpass-plugin=/usr/lib/mull-ir-frontend-12 -grecord-command-line -g

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CFLAGS := $(CFLAGS) -arch x86_64
endif

all: librope.a

clean:
	rm -f librope.a *.bc *.o tests

# You can add -emit-llvm here if you're using clang.
rope.o: rope.c rope.h
	$(CC) $(CFLAGS) $< -c -o $@

benchmark.o: test/benchmark.c
	$(CC) $(CFLAGS) $< -c -o $@

tests.o: test/tests.c
	$(CC) $(CFLAGS) $< -c -o $@

slowstring.o: test/slowstring.c
	$(CC) $(CFLAGS) $< -c -o $@

librope.a: rope.o
	ar rcs $@ $+

# Only need corefoundation to run the tests on mac
tests: tests.o benchmark.o slowstring.o librope.a
	$(CC) $(CFLAGS) $+ -o $@

