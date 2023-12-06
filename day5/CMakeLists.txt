cmake_minimum_required(VERSION 3.0.0)
project(DayThree VERSION 0.1.0)

FILE(COPY test-input DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY real-input DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(day5 day5.cpp)
add_executable(day5p2 day5p2.cpp)

set_target_properties(day5 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)

set_target_properties(day5p2 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)
