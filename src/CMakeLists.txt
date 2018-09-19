set(FIFTH_SRC file_utils.c lexer.c vm.c words.c program_stack.c
        stdlib/std_words.c stdlib/math.c
        dynamic_string.c call_stack.c)

add_library(fifth STATIC ${FIFTH_SRC})
add_executable(fifth_executable fifth.c)
target_link_libraries(fifth_executable fifth)