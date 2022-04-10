#!/usr/bin/env python3

from sh import bash

import os
import sys
import json


testcases=( 
    # "offbrand_lib",
    # "parson" ,
    # "shoco" ,
    # "binn" ,
    # "librope" ,
    # "fsm" ,
    "gaad" ,
    # "Stringy" ,
    # "trie" ,
    # "ujson" ,
)

opts = {
    "all": "wasmut.toml",
    "no-meta": "wasmut_no_meta.toml",
    "no-coverage": "wasmut_no_coverage.toml",
    "none": "wasmut_no_coverage_no_meta.toml",
}

for testcase in testcases:
    

    
    output_file = f"results/{testcase}.csv"

    with open(output_file, "w") as f:
        f.write(f"time;mutants;score;variant\n")

    for (variant, config) in opts.items():


        for i in range(5):
            os.chdir(f"../../code/{testcase}")
            print(f"Run {testcase}: {variant} run ", i)
            out = bash("run.sh", config)

            data = json.loads(out.stdout.decode("utf-8"))

            time = data["summary"]["execution_time"]
            mut = data["summary"]["mutants"]
            score = data["summary"]["mutation_score"]

            os.chdir(f"../../experiments/optimizations")

            with open(output_file, "a") as f:
                f.write(f"{time};{mut};{score};{variant}\n")
        
