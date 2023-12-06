cmake_minimum_required(VERSION 3.0.0)
project(DayTwo VERSION 0.1.0)

FILE(COPY input.txt DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(day2 day2.cpp)
add_executable(day2p2 day2p2.cpp)

set_target_properties(day2 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)

set_target_properties(day2p2 PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED YES
)
