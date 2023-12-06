cmake_minimum_required(VERSION 3.0.0)
project(AocDayOne VERSION 0.1.0)

FILE(COPY input.txt DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(day1 day1.cpp)
add_executable(day1p2 day1p2.cpp)

set_target_properties(day1 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)

set_target_properties(day1p2 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)
