cmake_minimum_required(VERSION 3.12)
project(fifth C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src)
add_subdirectory(test)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_FIFTH_DEBUG")