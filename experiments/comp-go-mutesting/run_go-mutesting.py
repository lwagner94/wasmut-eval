#!/usr/bin/env python3

from sh import bash
import os
import re
import sys

testcase = sys.argv[1]

os.chdir(f"../../code/{testcase}")



times = []
scores = []
mutants = []

for i in range(5):
    print("Run: ", i)
    out = bash("run_go_mutesting.sh")
    time = int(float(re.search(r"User time \(seconds\): (\d+\.\d+)", out.stderr.decode("utf-8")).group(1)) * 1000)
    score = float(re.search(r"mutation score is (\d+\.\d+)", out.stdout.decode("utf-8")).group(1)) * 100
    mut = int(re.search(r"total is (\d+)", out.stdout.decode("utf-8")).group(1))

    times.append(time)
    scores.append(score)
    mutants.append(mut)

os.chdir("../../experiments/comp-go-mutesting")

print(times)

output_file = f"results/{testcase}-go-mutesting.csv"
with open(output_file, "w") as f:
    f.write(f"time;mutants;score\n")

    for i in range(len(times)):
        f.write(f"{times[i]};{mutants[i]};{scores[i]}\n")
