

all: count_words.wasm count_words_opt.wasm


count_words.wasm: src/main.rs
	cargo wasi build
	cp target/wasm32-wasi/debug/rust.wasm count_words.wasm


count_words_opt.wasm: src/main.rs
	cargo wasi build --release
	cp target/wasm32-wasi/release/rust.wasm count_words_opt.wasm