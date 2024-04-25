cmake_minimum_required(VERSION 3.14)
project("HashPipe" C)

set(TARGET_GROUP production CACHE STRING "Group to build")

add_subdirectory("src/hash")
add_subdirectory("src/file")

if (TARGET_GROUP STREQUAL production)
    add_subdirectory("src/main"
    )
elseif (TARGET_GROUP STREQUAL test)
    include(CTest)
    add_subdirectory("lib")
    add_subdirectory("test")
else ()
    message(FATAL_ERROR "Given CMAKE_BUILD_TYPE unknown")
endif ()
