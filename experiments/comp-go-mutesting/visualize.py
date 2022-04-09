#!/usr/bin/env python3

def set_size(width_pt, fraction=1, subplots=(1, 1)):
    """Set figure dimensions to sit nicely in our document.

    Parameters
    ----------
    width_pt: float
            Document width in points
    fraction: float, optional
            Fraction of the width which you wish the figure to occupy
    subplots: array-like, optional
            The number of rows and columns of subplots.
    Returns
    -------
    fig_dim: tuple
            Dimensions of figure in inches
    """
    # Width of figure (in pts)
    fig_width_pt = width_pt * fraction
    # Convert from pt to inches
    inches_per_pt = 1 / 72.27

    # Golden ratio to set aesthetic figure height
    golden_ratio = (5**.5 - 1) / 2

    # Figure width in inches
    fig_width_in = fig_width_pt * inches_per_pt
    # Figure height in inches
    fig_height_in = fig_width_in * golden_ratio * (subplots[0] / subplots[1])

    return (fig_width_in, fig_height_in)



import pandas as pd
import numpy as np

import sys

# testcase = sys.argv[1]

testcases = ["fsm", "gaad", "Stringy", "trie", "ujson"]

results = pd.DataFrame()


for testcase in testcases:

    wasmut = pd.read_csv(f"results/{testcase}.csv", delimiter=";")
    go = pd.read_csv(f"results/{testcase}-go-mutesting.csv", delimiter=";")


    for (tool, tool_name) in ((wasmut, "wasmut"), (go, "go")):
        tool["time"] = tool["time"] / 1000
        tool["score"] = tool["score"].astype(float).round(1)

    t_wasmut = wasmut["time"].mean()
    tstd_wasmut = wasmut["time"].std()
    mutants_wasmut = wasmut["mutants"].mean()
    score_wasmut = wasmut["score"].mean()

    muts_per_sec_wasmut = mutants_wasmut / t_wasmut

    t_go =       go["time"].mean()
    tstd_go =    go["time"].std()
    mutants_go = go["mutants"].mean()
    score_go =   go["score"].mean()

    muts_per_sec_go = mutants_go / t_go

    row ={
        "testcase": testcase,
        "score_go": (score_go), 
        "score_wasmut": (score_wasmut), 
        "time_go": (t_go), 
        "time_std_go": (tstd_go), 
        "time_wasmut": (t_wasmut), 
        "time_std_wasmut": (tstd_wasmut), 
        "mutants_go": int(mutants_go),
        "mutants_wasmut": int(mutants_wasmut),
        "mutants_per_sec_go": (muts_per_sec_go),
        "mutants_per_sec_wasmut": (muts_per_sec_wasmut),
        }
    
    results = results.append(row, ignore_index=True)

    # print(df)
    # pd.concat(df)



    # wasmut = wasmut.std()


# wasmut["time"] = wasmut["time"] / 1000
# mull["time"] = mull["time"] / 1000


    # print(wasmut)
    # print(mull)


print(results.round(1))
# times["time"] = times["time"] / 1000
# mem["mem"] = mem["mem"] / 1000


# mean_time = times.groupby("threads").mean().reset_index()
# # mean_time.rename(columns={"time": "mean"}, inplace=True)
# stddev_time = times.groupby("threads").std().reset_index()
# stddev_time.rename(columns={"time": "time_stddev"}, inplace=True)

# mean_mem = mem.groupby("threads").mean().reset_index()
# # mean_mem.rename(columns={"mem": "mean"}, inplace=True)
# stddev_mem = mem.groupby("threads").std().reset_index()
# stddev_mem.rename(columns={"mem": "mem_stddev"}, inplace=True)

# import matplotlib as mpl

# mpl.use('pgf')

# import matplotlib.pyplot as plt
# import seaborn as sns

# # plt.style.use('seaborn')
# # But with fonts from the document body
# plt.rcParams.update({
#     "font.family": "serif",  # use serif/main font for text elements
#     "text.usetex": True,     # use inline math for ticks
#     "pgf.rcfonts": False     # don't setup fonts from rc parameters
#     })



# fig, ax = plt.subplots(1, 2, figsize=set_size(350))


# sns.set_theme(style="ticks", palette="pastel")


# sns.barplot(x="threads", y="time", data=mean_time, color="b", ax=ax[0])
# sns.barplot(x="threads", y="mem", data=mean_mem, color="b", ax=ax[1])

# ax[0].set_xlabel('Threads')
# ax[0].set_ylabel('Execution time [s]')
# ax[1].set_xlabel('Threads')
# ax[1].set_ylabel('Memory use [MB]')

# # plt.xlabel('Threads')
# # plt.ylabel('Execution Time (s)')

# fig.tight_layout()

# plt.savefig(f"threads_{testcase}.pgf", format="pgf")

# joined_time = mean_time.join(stddev_time.set_index("threads"), on="threads").round(1)
# joined_mem = mean_mem.join(stddev_mem.set_index("threads"), on="threads").round(1)


# a = joined_time.join(joined_mem.set_index("threads"), on="threads")


# print(a)


