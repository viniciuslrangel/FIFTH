//
// Created by vinic on 07/09/18.
//

#include "math.h"
#include "../program_stack.h"
#include "../words.h"

void math_add(ProgramStack stack) {
    number_t n1, n2;
    POP_NUMBER(n1, stack);
    POP_NUMBER(n2, stack);
    PStack_push(stack, STACK_NUMBER(n1 + n2));
}

void math_sub(ProgramStack stack) {
    number_t n1, n2;
    POP_NUMBER(n1, stack);
    POP_NUMBER(n2, stack);
    PStack_push(stack, STACK_NUMBER(n1 - n2));
}

void math_mul(ProgramStack stack) {
    number_t n1, n2;
    POP_NUMBER(n1, stack);
    POP_NUMBER(n2, stack);
    PStack_push(stack, STACK_NUMBER(n1 * n2));
}

void math_div(ProgramStack stack) {
    number_t n1, n2;
    POP_NUMBER(n1, stack);
    POP_NUMBER(n2, stack);
    PStack_push(stack, STACK_NUMBER(n1 / n2));
}

void RegisterMathWords() {
    struct WordEntry wordEntry[] = {
                {"+",     math_add},
                {"-",     math_sub},
                {"*",     math_mul},
                {"/",     math_div}
        };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
}
