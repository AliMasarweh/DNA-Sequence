cmake_minimum_required(VERSION 3.17)
project(dna_sequence)

set(CMAKE_CXX_STANDARD 20)

include_directories(src header production)

add_executable(dna_sequence main.cpp)
add_executable(test_production production/test.cpp)

target_link_libraries(test_production gtest gtest_main pthread)
target_link_libraries(dna_sequence gtest gtest_main pthread)

add_test(test_production test_production)
