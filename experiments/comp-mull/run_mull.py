

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
    out = bash("run.sh")
    time = int(re.search(r"execution time: (\d+)ms", out.stdout.decode("utf-8")).group(1))
    score = int(re.search(r"Mutation score: (\d+)\%", out.stdout.decode("utf-8")).group(1))
    mut = int(re.search(r"Survived mutants \(\d+\/(\d+)\)", out.stdout.decode("utf-8")).group(1))

    times.append(time)
    scores.append(score)
    mutants.append(mut)

os.chdir("../../experiments/comp-mull")

print(times)

output_file = f"results/{testcase}.csv"
with open(output_file, "w") as f:
    f.write(f"time;mutants;score\n")

    for i in range(len(times)):
        f.write(f"{times[i]};{mutants[i]};{scores[i]}\n")
