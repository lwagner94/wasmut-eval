

all: count_words.wasm  count_words_opt.wasm


count_words.wasm: count_words.go
	tinygo build -target wasi -opt 0 -o count_words.wasm

count_words_opt.wasm: count_words.go
	tinygo build -target wasi -opt z -o count_words_opt.wasm


clean: 
	rm -f count_words.wasm
	rm -f count_words_opt.wasm

# count_words_opt.wasm: count_words.wasm
# 	cargo wasi build --release
# 	cp target/wasm32-wasi/release/rust.wasm count_words_opt.wasm