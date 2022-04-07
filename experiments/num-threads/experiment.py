#!/usr/bin/env python3

from sh import wasmut
from sh import mkdir
import json 

testcase = "modules/gaad"


mkdir("-p", "results")



file = testcase + ".wasm"
config = testcase + ".toml"

output_file = f"results/{testcase}.csv"
with open(output_file, "w") as f:
            f.write(f"threads;time\n")

for t in [1,2,4,8]:
    
    for run in range(0, 10):
        print(f"{file}: {t} Threads, run {run}")
        out = wasmut.mutate(file, "-c", config, "-r", "json", "-t", t)

        summary = json.loads(out.stdout)["summary"]
        execution_time = summary["execution_time"]

        with open(output_file, "a") as f:
            f.write(f"{t};{execution_time}\n")


