cmake_minimum_required(VERSION 3.27)
project(HashPipe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

<<<<<<< Updated upstream
add_subdirectory("src/hash")

if (TARGET_GROUP STREQUAL production)
    add_executable(HashPipe
            "src/main.c"
    )
elseif (TARGET_GROUP STREQUAL test)
    include(CTest)
    add_subdirectory("lib")
    add_subdirectory("test")
else ()
    message(FATAL_ERROR "Given CMAKE_BUILD_TYPE unknown")
endif ()
=======
add_subdirectory("src")
>>>>>>> Stashed changes
