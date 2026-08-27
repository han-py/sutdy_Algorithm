cmake_minimum_required(VERSION 4.2)
project(DataStructures)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-D ACM_LOCAL)

add_executable(DataStructures
        main.cpp
)
target_link_libraries(DataStructures)

add_executable(QuickSort_WD
        WangDao_2027/01_SequentialList/02_QuickSort_WD.cpp)
target_compile_definitions(QuickSort_WD PRIVATE RUN_QIUCKSORT_WD)
