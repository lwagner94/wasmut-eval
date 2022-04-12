#!/usr/bin/env python3


import pandas as pd
import numpy as np

data = pd.read_csv(f"results/results.csv", delimiter=";")

# data["time"] = data["time"] / 1000

print(data)


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
import sys


plt.rcParams.update({
    "font.family": "serif",  # use serif/main font for text elements
    "text.usetex": True,     # use inline math for ticks
    "pgf.rcfonts": False     # don't setup fonts from rc parameters
    })


if len(sys.argv) == 2 and sys.argv[1] == "time":
    fig, ax = plt.subplots(1, 1, figsize=set_size(300))
    sns.set_theme(style="ticks", palette="pastel")
    sns.barplot(x="testcase_variant", y="time", data=data, color="b", ax=ax,)
    ax.set_xlabel('')
    ax.set_ylabel('Time [ms]')
    for tick in ax.get_xticklabels():
        tick.set_rotation(90)
    plt.yscale("log")
    fig.tight_layout()
    plt.savefig(f"lang_time.pgf", format="pgf")


if len(sys.argv) == 2 and sys.argv[1] == "mutants":
    fig, ax = plt.subplots(1, 1, figsize=set_size(300))
    sns.set_theme(style="ticks", palette="pastel")
    sns.barplot(x="testcase_variant", y="mutants", data=data, color="b", ax=ax,)
    ax.set_xlabel('')
    ax.set_ylabel('Mutants')
    for tick in ax.get_xticklabels():
        tick.set_rotation(90)
    fig.tight_layout()
    plt.savefig(f"lang_mutants.pgf", format="pgf")


if len(sys.argv) == 2 and sys.argv[1] == "score":

    fig, ax = plt.subplots(1, 1, figsize=set_size(300))
    sns.set_theme(style="ticks", palette="pastel")
    sns.barplot(x="testcase_variant", y="score", data=data, color="b", ax=ax,)
    ax.set_xlabel('')
    ax.set_ylabel('Score [%]')
    for tick in ax.get_xticklabels():
        tick.set_rotation(90)
    fig.tight_layout()
    plt.savefig(f"lang_score.pgf", format="pgf")


#plt.show()


grouped = data.groupby("testcase_variant").mean()
stdev = data.groupby("testcase_variant").std()

grouped.insert(1, "time_stdev", stdev["time"])

print(grouped.round(1))