#!/bin/bash

export CC=clang
export CFLAGS="--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot -g -O0"
export LDFLAGS="--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot"

make check

