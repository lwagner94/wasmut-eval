#!/usr/bin/env bash

wasmut mutate test.wasm -c $1 -r json  -t $2