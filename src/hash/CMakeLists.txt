cmake_minimum_required(VERSION 3.14)
project(hash)

add_library(hash STATIC
        "src/hash.c"
)

target_include_directories(hash PUBLIC "include")