cmake_minimum_required(VERSION 4.2)
project(DataStructures)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-D ACM_LOCAL)

add_executable(DataStructures
        main.cpp
)

# Separate executable for the QuickSort example so it doesn't conflict with the
# project `main`. This target will compile the file that contains a standalone
# `main()` for quicksort (guarded by RUN_QIUCKSORT_WD).
add_executable(QuickSort_WD
        WangDao_2027/01_SequentialList/02_QuickSort_WD.cpp)
target_compile_definitions(QuickSort_WD PRIVATE RUN_QIUCKSORT_WD)
