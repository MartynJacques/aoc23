cmake_minimum_required(VERSION 3.0)
project(AoC2023)

set(CMAKE_CXX_STANDARD 17)

foreach(DAY RANGE 1 16)
    add_subdirectory(day${DAY})
endforeach()
