

all: count_words.wasm count_words_opt.wasm


count_words.wasm: count_words.cpp
	clang++ --target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot -g -O0 -o $@ $<

count_words_opt.wasm: count_words.wasm
	wasm-opt -g -O3 $< -o $@
	

.PHONY: clean
clean:
	rm -f count_words.wasm
	rm -f count_words_opt.wasm


