#!/bin/bash

sh autogen.sh

export CC=clang
export CFLAGS="--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot -g"
export RANLIB=llvm-ranlib
export AR=llvm-ar
./configure --host=wasm32-wasi
make clean
make check