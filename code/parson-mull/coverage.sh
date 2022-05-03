#!/bin/bash


make -f make_coverage clean
make -f make_coverage test

./test


grcov . -s . --binary-path ./ -t html --branch --ignore-not-existing -o ./coverage --ignore "src/tests/*"
