cmake_minimum_required(VERSION 3.17)
project(dna_sequence)

set(CMAKE_CXX_STANDARD 20)

include_directories(src header production)

add_executable(dna_sequence main.cpp)
add_executable(test production/test.cpp)