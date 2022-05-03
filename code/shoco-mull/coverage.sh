#!/bin/bash

#!/bin/bash

export CC=clang
export CFLAGS="-O0 --coverage" LDFLAGS="--coverage"

# make check

make -f make_coverage clean
make -f make_coverage check

./tests


grcov . -s . --binary-path ./ -t html --branch --ignore-not-existing -o ./coverage --ignore "tests.c"
