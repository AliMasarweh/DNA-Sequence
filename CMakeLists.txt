cmake_minimum_required(VERSION 3.17)
project(dna_sequence)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(header)
add_subdirectory(production)

add_executable(dna_sequence main.cpp)
add_executable(test_production production/test.cpp)

link_directories(${MyProject_SOURCE_DIR}/src/CMakeLists.txt)

target_link_libraries(dna_sequence SRC)
target_link_libraries(test_production gtest gtest_main pthread)
target_link_libraries(test_production SRC)

#add_executable(quick_tests quick_tests.cpp)
#target_link_libraries(quick_tests SRC)
