cmake_minimum_required(VERSION 3.14)
project(file)

add_library(file STATIC
        "src/file.c"
        "src/fileread.c"
)

target_include_directories(file PUBLIC "include")