#!/usr/bin/env python3

from sh import bash
import sh
import os
import sys
import json
import re


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



for testcase in testcases:
    output_file = f"results/{testcase}.csv"

    with open(output_file, "w") as f:
        f.write(f"time;mem;threads\n")

    for threads in [1,2,4,8]:
        for i in range(3):
            os.chdir(f"../../code/{testcase}")
            print(f"Run {testcase}: {threads} run ", i)
            out = sh.time("-v", "bash", "run.sh", "wasmut.toml", threads)

            data = json.loads(out.stdout.decode("utf-8"))

            time = data["summary"]["execution_time"]
            mem = int(re.search(r"Maximum resident set size \(kbytes\): (\d+)", out.stderr.decode("utf-8")).group(1))

            print(time, mem)

            os.chdir(f"../../experiments/num-threads")

            with open(output_file, "a") as f:
                f.write(f"{time};{mem};{threads}\n")
            
