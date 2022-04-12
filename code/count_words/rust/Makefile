

all: count_words.wasm count_words_opt.wasm


count_words.wasm: src/main.rs
	cargo wasi build
	cp target/wasm32-wasi/debug/rust.wasm count_words.wasm


count_words_opt.wasm: count_words.wasm
	wasm-opt -g -O3 $< -o $@

clean: 
	rm -f count_words.wasm
	rm -f count_words_opt.wasm
	cargo clean