cmake_minimum_required(VERSION 3.14)
project(hash)

add_library(hash STATIC
        "src/HashDirectory.cpp"
        "src/HashBucket.cpp"
)

target_include_directories(hash PUBLIC "include")