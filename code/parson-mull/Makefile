
CC = clang-12
CFLAGS = -g -Wall -Wextra -std=c89 -pedantic-errors -DTESTS_MAIN -O0 -fexperimental-new-pass-manager -fpass-plugin=/usr/lib/mull-ir-frontend-12 -grecord-command-line

all: test 

.PHONY: test testcpp test_hash_collisions
test: tests.c parson.c
	$(CC) $(CFLAGS) -o t.o -c tests.c
	$(CC) $(CFLAGS) -o p.o -c parson.c
	$(CC) $(CFLAGS) t.o p.o -o $@



clean:
	rm -f test *.o

