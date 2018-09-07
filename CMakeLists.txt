cmake_minimum_required(VERSION 3.12)
project(fifth C)

set(CMAKE_C_STANDARD 99)

add_executable(fifth main.c
        fileUtils.c lexer.c vm.c words.c program_stack.c
        stdlib/std_words.c stdlib/math.c
        dynamic_string.c)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_FIFTH_DEBUG")