#!/usr/bin/env python3

testcases=( 
    # "offbrand_lib",
    # "parson" ,
    # "shoco" ,
    "binn" ,
    # "librope" ,
    "fsm" ,
    # "gaad" ,
    # "Stringy" ,
    "trie" ,
    "ujson" ,
)


import pandas as pd
import numpy as np

import sys

# testcase = sys.argv[1]

# testcases = ["fsm", "gaad", "Stringy", "trie", "ujson"]

results = pd.DataFrame()


for testcase in testcases:

    wasmut = pd.read_csv(f"results/{testcase}.csv", delimiter=";")

    
    wasmut["time"] = wasmut["time"] / 1000
     

    # t_wasmut = wasmut["time"].mean()
    # tstd_wasmut = wasmut["time"].std()
    # mutants_wasmut = wasmut["mutants"].mean()
    # score_wasmut = wasmut["score"].mean()

    time = wasmut.groupby("threads", as_index=False)["time"].mean()
    mem = wasmut.groupby("threads")["mem"].mean() / 1000
    time = pd.DataFrame(time)
    mem = pd.DataFrame(mem)

    time = time.join(mem, on="threads")


    print()
    print()
    print(testcase)
    print(time.round(1))

    norml = time.div(time.iloc[0])

    results = pd.concat([results, norml])

results = results.groupby("threads", as_index=False).mean()

results["threads"] = results["threads"].astype(int)

print(results.round(2))


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



import matplotlib as mpl

mpl.use('pgf')

import matplotlib.pyplot as plt
import seaborn as sns

# plt.style.use('seaborn')
# But with fonts from the document body
plt.rcParams.update({
    "font.family": "serif",  # use serif/main font for text elements
    "text.usetex": True,     # use inline math for ticks
    "pgf.rcfonts": False     # don't setup fonts from rc parameters
    })



fig, ax = plt.subplots(1, 2, figsize=set_size(350))


sns.set_theme(style="ticks", palette="pastel")


sns.barplot(x="threads", y="time", data=results, color="b", ax=ax[0])
sns.barplot(x="threads", y="mem", data=results, color="b", ax=ax[1])

ax[0].set_xlabel('Threads')
ax[0].set_ylabel('Execution time')
ax[1].set_xlabel('Threads')
ax[1].set_ylabel('Memory use')


fig.tight_layout()

plt.savefig(f"threads_avg.pgf", format="pgf")

