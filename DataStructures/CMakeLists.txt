cmake_minimum_required(VERSION 4.2)
project(DataStructures)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-D ACM_LOCAL)

add_executable(DataStructures
        main.cpp)
target_link_libraries(DataStructures)

add_executable(WD_01_SequentialList_02_QuickSort_02_QuickSort
        WangDao_2027/01_SequentialList/02_QuickSort/02_QuickSort.cpp)
target_compile_definitions(WD_01_SequentialList_02_QuickSort_02_QuickSort PRIVATE RUN_QIUCKSORT_WD)

add_executable(WD_01_SequentialList_04_OptimizedSolution_01-04_template1_equivalent
        WangDao_2027/01_SequentialList/04_OptimizedSolution/01-04_template1_equivalent.cpp)
target_compile_definitions(WD_01_SequentialList_04_OptimizedSolution_01-04_template1_equivalent PRIVATE RUN_TEMPLATE1_EQUIVALENT_WD)
