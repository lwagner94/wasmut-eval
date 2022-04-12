

all: count_words.wasm  count_words_opt.wasm


count_words.wasm: count_words.go
	tinygo build -target wasi -opt 0 -o count_words.wasm

count_words_opt.wasm: count_words.wasm
	wasm-opt -g -O3 $< -o $@

clean: 
	rm -f count_words.wasm
	rm -f count_words_opt.wasm
