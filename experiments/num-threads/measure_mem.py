#!/usr/bin/env python3

from sh import wasmut
from sh import mkdir
from sh import time
import json 
import sys

import re



testcase = sys.argv[1]


mkdir("-p", "results")


file = "modules/" + testcase + ".wasm"
config = "modules/" + testcase + ".toml"

output_file = f"results/{testcase}_mem.csv"
with open(output_file, "w") as f:
    f.write(f"threads;mem\n")

for t in [1, 2, 4, 8]:
    
    for run in range(0, 10):
        print(f"{file}: {t} Threads, run {run}")
        out = time("-v", "wasmut", "mutate", file, "-c", config, "-r", "json", "-t", t)

        # print(out.stderr)

        mem = int(re.search(r"Maximum resident set size \(kbytes\): (\d+)", out.stderr.decode("utf-8")).group(1))

        # summary = json.loads(out.stdout)["summary"]
        # execution_time = summary["execution_time"]

        with open(output_file, "a") as f:
            f.write(f"{t};{mem}\n")


