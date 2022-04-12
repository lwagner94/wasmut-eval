

CC=clang++
CFLAGS=--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot -g -O0




.PHONY: all
all: count_words.wasm

count_words.wasm: count_words.cpp
	$(CC) $(CFLAGS) -o $@ $<



.PHONY: clean
clean:
	rm -f count_words.wasm



