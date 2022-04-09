#!/usr/bin/env python3

from sh import bash
import os
import sys
import json

testcase = sys.argv[1]

os.chdir(f"../../code/{testcase}")



times = []
scores = []
mutants = []

for i in range(5):
    print("Run: ", i)
    out = bash("run.sh")

    print(out)

    data = json.loads(out.stdout.decode("utf-8"))

    time = data["summary"]["execution_time"]
    mut = data["summary"]["mutants"]
    score = data["summary"]["mutation_score"]
    
    times.append(time)
    scores.append(score)
    mutants.append(mut)

os.chdir("../../experiments/comp-go-mutesting")

print(times)
print(scores)
print(mutants)

output_file = f"results/{testcase}.csv"
with open(output_file, "w") as f:
    f.write(f"time;mutants;score\n")

    for i in range(len(times)):
        f.write(f"{times[i]};{mutants[i]};{scores[i]}\n")
