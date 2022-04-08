#!/bin/bash

export CC=clang
export CFLAGS="--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot -g"
export LDFLAGS="--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot"

make check

