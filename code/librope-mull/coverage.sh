make -f make_coverage clean
make -f make_coverage tests
./tests

grcov . -s . --binary-path ./ -t html --branch --ignore-not-existing -o ./coverage
