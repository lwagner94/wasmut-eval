#!/usr/bin/env python

testcases=( 
    "offbrand_lib",
    "parson" ,
    "shoco" ,
    "binn" ,
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

    mean = wasmut.groupby("variant")["time"].mean()
    std = wasmut.groupby("variant")["time"].std()

    row = {
        "testcase": testcase,
        "time_none": mean["none"],
        # "std_none": std["none"],
        "time_no_meta": mean["no-meta"],
        # "std_no_meta": std["no-meta"],
        "time_no_coverage": mean["no-coverage"],
        # "std_no_coverage": std["no-coverage"],
        "time_all": mean["all"],
        # "std_all": std["all"],
    }

    results = results.append(row, ignore_index=True)

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

normalized = results.copy()


normalized["time_no_meta"] = 100 * normalized["time_no_meta"] / normalized["time_none"]
normalized["time_no_coverage"] = 100 * normalized["time_no_coverage"] / normalized["time_none"]
normalized["time_all"] = 100 * normalized["time_all"] / normalized["time_none"]
normalized["time_none"] = 100 * normalized["time_none"] / normalized["time_none"]



print(results.round(1))







row = {
    "testcase": "Average",
    "time_none": normalized["time_none"].mean(),
    "time_no_meta": normalized["time_no_meta"].mean(),
    "time_no_coverage": normalized["time_no_coverage"].mean(),
    "time_all": normalized["time_all"].mean(),
}

normalized = normalized.append(row, ignore_index=True)


# normalized = normalized * 100

print(normalized.round(0))