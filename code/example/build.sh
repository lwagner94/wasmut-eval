#!/bin/bash

clang --target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot -g -O0 -o main.wasm main.c