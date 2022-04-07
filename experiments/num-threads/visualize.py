
import pandas as pd
import numpy as np

testcase = "gaad"

df = pd.read_csv(f"results/{testcase}.csv", delimiter=";")

df["time"] = df["time"] / 1000


mean = df.groupby("threads").mean().reset_index()
mean.rename(columns={"time": "mean"}, inplace=True)
stddev = df.groupby("threads").std().reset_index()
stddev.rename(columns={"time": "stddev"}, inplace=True)


import matplotlib.pyplot as plt
import seaborn as sns
sns.set_theme(style="ticks", palette="pastel")


sns.barplot(x="threads", y="mean", data=mean, color="b")


plt.xlabel('Threads')
plt.ylabel('Execution Time (s)')

# plt.savefig(f"{testcase}.png")

joined = mean.join(stddev.set_index("threads"), on="threads").round(decimals=1)

print(joined)