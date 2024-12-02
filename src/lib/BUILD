load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "TrieTree",
    srcs = ["trietree.cc"],
    hdrs = ["trietree.h"],
    visibility = ["//visibility:public"], 
)

cc_library(
    name = "UnionFind",
    srcs = ["unionfind.cc"],
    hdrs = ["unionfind.h"],
    visibility = ["//visibility:public"],    
)

cc_library(
    name = "UnionFind_Gas",
    srcs = ["unionfind_gas.cc"],
    hdrs = ["unionfind_gas.h"],
    visibility = ["//visibility:public"],    
)

cc_library(
    name = "TrojanMap",
    srcs = ["trojanmap.cc"],
    hdrs = ["trojanmap.h"],
    data = ["data.csv"],
    deps = ["//src/lib:TrieTree",
            "//src/lib:UnionFind",
            "//src/lib:UnionFind_Gas"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "MapUI",
    srcs = ["mapui.cc"],
    hdrs = ["mapui.h"],
    deps = ["@opencv//:opencv", "//src/lib:TrojanMap", "//src/lib:UI", "@ncurses//:main"],
    data = ["data.csv", 
    "map.png", 
    "output0.avi","output0_2opt.avi","output0_backtracking.avi"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "UI",
    srcs = glob(["ui.cc"]),
    hdrs = glob(["ui.h"]),
    deps = ["@ncurses//:main"],
    visibility = ["//visibility:public"],
)