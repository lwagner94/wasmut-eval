make -f make_coverage test
test/test_binn

grcov . -s . --binary-path ./test/ -t html --branch --ignore-not-existing -o ./coverage
