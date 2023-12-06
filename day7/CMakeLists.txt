cmake_minimum_required(VERSION 3.0.0)
project(AoC VERSION 0.1.0)

add_executable(day7 day7.cpp)
add_executable(day7p2 day7p2.cpp)

set_target_properties(day7 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)

set_target_properties(day7p2 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)
