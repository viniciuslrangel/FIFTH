set(FIFTH_SRC file_utils.c lexer.c vm.c words.c program_stack.c
        stdlib/std_words.c stdlib/math.c
        dynamic_string.c runtime_impl.h)

add_executable(fifth fifth.c ${FIFTH_SRC})