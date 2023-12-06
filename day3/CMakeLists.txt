cmake_minimum_required(VERSION 3.0.0)
project(DayThree VERSION 0.1.0)

FILE(COPY input.txt DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(day3 day3.cpp)
add_executable(day3p2 day3p2.cpp)

set_target_properties(day3 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)

set_target_properties(day3p2 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)
