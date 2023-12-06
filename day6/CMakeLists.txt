cmake_minimum_required(VERSION 3.0.0)
project(DayThree VERSION 0.1.0)

add_executable(day6 day6.cpp)
add_executable(day6p2 day6p2.cpp)

set_target_properties(day6 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)

set_target_properties(day6p2 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)
