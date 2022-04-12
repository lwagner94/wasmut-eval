#!/usr/bin/env python3

from sh import bash
from sh import wasmut

import os
import sys
import json


testcases=( 
    ("c", "C"),
    ("c++", "C++"),
    ("go", "Go"),
    ("rust", "Rust"),
)


output_file = f"results/results.csv"

with open(output_file, "w") as f:
    f.write(f"time;mutants;score;testcase_variant\n")

for (testcase, name) in testcases:
    for file in ("count_words.wasm", "count_words_opt.wasm"):
        for i in range(20):
            os.chdir(f"../../code/count_words/{testcase}")
            print(f"Run {testcase}: {file} run ", i)
            out = wasmut("mutate", file, "-C", "-r", "json")

            data = json.loads(out.stdout.decode("utf-8"))

            time = data["summary"]["execution_time"]
            mut = data["summary"]["mutants"]
            score = data["summary"]["mutation_score"]

            os.chdir(f"../../../experiments/languages")

            variant = name

            if "opt" in file:
                variant += " (opt)"

            with open(output_file, "a") as f:
                f.write(f"{time};{mut};{score};{variant}\n")
        
