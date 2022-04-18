#!/usr/bin/env python3

from sh import bash

import os
import sys
import json


testcases=( 
    "offbrand_lib",
    "parson" ,
    "shoco" ,
    "binn" ,
    "librope" ,
    "fsm" ,
    "gaad" ,
    "Stringy" ,
    "trie" ,
    "ujson" ,
)

output_file = f"results/results.csv"

# with open(output_file, "w") as f:
#     f.write(f"testcase;time;mutants;score;samples\n")

for testcase in testcases:
    for samples in [10,20,30,40,50]:
        for i in range(15):
            os.chdir(f"../../code/{testcase}")
            print(f"Run {testcase}: {samples} run ", i)
            out = bash("run.sh", "-c", "wasmut_no_coverage.toml", "-t", "8", "-s", samples)

            data = json.loads(out.stdout.decode("utf-8"))

            time = data["summary"]["execution_time"]
            mut = data["summary"]["mutants"]
            score = data["summary"]["mutation_score"]

            os.chdir(f"../../experiments/sampling")

            with open(output_file, "a") as f:
                f.write(f"{testcase};{time};{mut};{score};{samples}\n")

        
