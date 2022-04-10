#!/bin/bash

testcases=( \
    "offbrand_lib"\
    "parson" \
    "shoco" \
    "binn" \
    "librope" \
    "fsm" \
    "gaad" \
    "Stringy" \
    "trie" \
    "ujson" \
)

for tc in "${testcases[@]}"
do 
  cd ../../code/$tc
  cp wasmut.toml wasmut_no_coverage.toml
  cp wasmut.toml wasmut_no_meta.toml
  cp wasmut.toml wasmut_no_coverage_no_meta.toml

  echo "[engine]" >> wasmut_no_coverage.toml
  echo "coverage_based_execution = false" >> wasmut_no_coverage.toml


  echo "[engine]" >> wasmut_no_meta.toml
  echo "meta_mutant = false" >> wasmut_no_meta.toml


  echo "[engine]" >> wasmut_no_coverage_no_meta.toml
  echo "meta_mutant = false" >> wasmut_no_coverage_no_meta.toml
  echo "coverage_based_execution = false" >> wasmut_no_coverage_no_meta.toml
done