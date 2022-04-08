#!/bin/bash

export CC=clang-12
export CFLAGS="-O0 -fexperimental-new-pass-manager -fpass-plugin=/usr/lib/mull-ir-frontend-12 -g -grecord-command-line -fprofile-instr-generate -fcoverage-mapping"

make check

