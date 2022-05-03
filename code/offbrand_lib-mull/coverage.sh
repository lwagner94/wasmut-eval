#!/bin/bash


make -f make_coverage clean
make -f make_coverage

bin/tests/test_test


grcov . -s . --binary-path ./bin/tests/ -t html --branch --ignore-not-existing -o ./coverage --ignore "src/tests/*"
