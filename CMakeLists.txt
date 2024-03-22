project(turing)
cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(turing-project/include)

file(GLOB_RECURSE SOURCES
    turing-project/main.cpp
    turing-project/include/*.h
    turing-project/src/*.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(turing ${SOURCES})
