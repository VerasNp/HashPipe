cmake_minimum_required(VERSION 3.14)
project(database)
add_library(database STATIC
        "src/Database.cpp"
)
target_include_directories(database PUBLIC "include")
target_link_libraries(database
        hash)