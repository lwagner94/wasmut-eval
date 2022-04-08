#!/bin/bash

sh autogen.sh

export CC=clang-12
export CFLAGS="-fexperimental-new-pass-manager -fpass-plugin=/usr/lib/mull-ir-frontend-12 -grecord-command-line -g -O0"
./configure
make clean
make check