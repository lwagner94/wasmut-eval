

CC=clang
CFLAGS=--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot -g -O0


SRC=count_words.c
BINARY=test.wasm

OBJ=$(patsubst %.c,%.o.wasm,$(SRC))
#OBJ_WAT=$(patsubst %.c,%.o.wat,$(SRC))
#BINARY_WAT=$(patsubst %.wasm,%.wat,$(BINARY))

RUNTIME=wasmer


#%.wat : %.wasm
#	wasm2wat -o $@ $< 

.PHONY: all
all: count_words.wasm

count_words.wasm: count_words.c
	$(CC) $(CFLAGS) -o $@ $<



.PHONY: clean
clean:
	rm -f count_words.wasm



