#!/usr/bin/env python

testcases=( 
    "offbrand_lib",
    "parson" ,
    "shoco" ,
    # "binn" ,
    "librope" ,
    "fsm" ,
    "gaad" ,
    "Stringy" ,
    "trie" ,
    "ujson" ,
)


import pandas as pd
import numpy as np

import sys


data = pd.read_csv(f"results/results.csv", delimiter=";")

data["time"] = data["time"] / 1000

mean = data.groupby(by=["testcase", "samples"]).mean()
std = data.groupby(by=["testcase", "samples"]).std()

mean["score_std"] = std["score"].round(1)
mean["score"] = mean["score"].round(1)
mean["mutants"] = mean["mutants"].round(0).astype(int)
mean["time"] = mean["time"].round(1)


print(mean)
# print(std)

# testcase = sys.argv[1]

# testcases = ["fsm", "gaad", "Stringy", "trie", "ujson"]

# results = pd.DataFrame()


# for testcase in testcases:

#     wasmut = pd.read_csv(f"results/{testcase}.csv", delimiter=";")

    
#     wasmut["time"] = wasmut["time"] / 1000
     

#     # t_wasmut = wasmut["time"].mean()
#     # tstd_wasmut = wasmut["time"].std()
#     # mutants_wasmut = wasmut["mutants"].mean()
#     # score_wasmut = wasmut["score"].mean()

#     mean = wasmut.groupby("variant")["time"].mean()
#     std = wasmut.groupby("variant")["time"].std()

#     row = {
#         "testcase": testcase,
#         "time_none": mean["none"],
#         # "std_none": std["none"],
#         "time_no_meta": mean["no-meta"],
#         # "std_no_meta": std["no-meta"],
#         "time_no_coverage": mean["no-coverage"],
#         # "std_no_coverage": std["no-coverage"],
#         "time_all": mean["all"],
#         # "std_all": std["all"],
#     }

#     results = results.append(row, ignore_index=True)

    # print(mean["all"])

    # muts_per_sec_wasmut = mutants_wasmut / t_wasmut

    # t_go =       go["time"].mean()
    # tstd_go =    go["time"].std()
    # mutants_go = go["mutants"].mean()
    # score_go =   go["score"].mean()

    # muts_per_sec_go = mutants_go / t_go

    # row ={
    #     "testcase": testcase,
    #     "score_go": (score_go), 
    #     "score_wasmut": (score_wasmut), 
    #     "time_go": (t_go), 
    #     "time_std_go": (tstd_go), 
    #     "time_wasmut": (t_wasmut), 
    #     "time_std_wasmut": (tstd_wasmut), 
    #     "mutants_go": int(mutants_go),
    #     "mutants_wasmut": int(mutants_wasmut),
    #     "mutants_per_sec_go": (muts_per_sec_go),
    #     "mutants_per_sec_wasmut": (muts_per_sec_wasmut),
    #     }
    
    # results = results.append(row, ignore_index=True)

    # print(df)
    # pd.concat(df)



    # wasmut = wasmut.std()


# wasmut["time"] = wasmut["time"] / 1000
# mull["time"] = mull["time"] / 1000


    # print(wasmut)
    # print(mull)


# print(results.round(1))

# normalized = results.copy()


# normalized["time_no_meta"] = 1 / (normalized["time_no_meta"] / normalized["time_none"])
# normalized["time_no_coverage"] = 1 / (normalized["time_no_coverage"] / normalized["time_none"])
# normalized["time_all"] = 1 / (normalized["time_all"] / normalized["time_none"])
# normalized["time_none"] = 1 / (normalized["time_none"] / normalized["time_none"])



# print(results.round(1))









# row = {
#     "testcase": "Average",
#     "time_none": normalized["time_none"].mean(),
#     "time_none_std": normalized["time_none"].std(),
#     "time_no_meta": normalized["time_no_meta"].mean(),
#     "time_no_meta_std": normalized["time_no_meta"].std(),
#     "time_no_coverage": normalized["time_no_coverage"].mean(),
#     "time_no_coverage_std": normalized["time_no_coverage"].std(),
#     "time_all": normalized["time_all"].mean(),
#     "time_all_std": normalized["time_all"].std(),
# }

# avg = pd.DataFrame(row, index=[0])

# print(normalized.round(2))

# print(avg.round(2))


# def set_size(width_pt, fraction=1, subplots=(1, 1)):
#     """Set figure dimensions to sit nicely in our document.

#     Parameters
#     ----------
#     width_pt: float
#             Document width in points
#     fraction: float, optional
#             Fraction of the width which you wish the figure to occupy
#     subplots: array-like, optional
#             The number of rows and columns of subplots.
#     Returns
#     -------
#     fig_dim: tuple
#             Dimensions of figure in inches
#     """
#     # Width of figure (in pts)
#     fig_width_pt = width_pt * fraction
#     # Convert from pt to inches
#     inches_per_pt = 1 / 72.27

#     # Golden ratio to set aesthetic figure height
#     golden_ratio = (5**.5 - 1) / 2

#     # Figure width in inches
#     fig_width_in = fig_width_pt * inches_per_pt
#     # Figure height in inches
#     fig_height_in = fig_width_in * golden_ratio * (subplots[0] / subplots[1])

#     return (fig_width_in, fig_height_in)



# import matplotlib as mpl

# mpl.use('pgf')

# import matplotlib.pyplot as plt
# import seaborn as sns


# plt.rcParams.update({
#     "font.family": "serif",  # use serif/main font for text elements
#     "text.usetex": True,     # use inline math for ticks
#     "pgf.rcfonts": False     # don't setup fonts from rc parameters
#     })

# name_map = {
#     "time_none": "None",
#     "time_no_meta": "Coverage",
#     "time_no_coverage": "Meta",
#     "time_all": "Both",
# }


# plot_data = pd.DataFrame()

# for a in normalized:
#     if a == "testcase":
#         continue
    
#     series = normalized[a]

#     row = {
#         "field": name_map[a],
#         "data": series,
#     }

#     df = pd.DataFrame(row)

    
#     plot_data = plot_data.append(df)
    


# print(plot_data)


# fig, ax = plt.subplots(1, 1, figsize=set_size(300))


# sns.set_theme(style="ticks", palette="pastel")




# sns.barplot(x="field", y="data", data=plot_data, color="b", ax=ax,)

# ax.set_xlabel('Optimization')
# ax.set_ylabel('Speed-up')
# # ax[1].set_xlabel('Threads')
# # ax[1].set_ylabel('Memory use')


# fig.tight_layout()

# plt.savefig(f"opt_avg.pgf", format="pgf")

# # plt.show()
