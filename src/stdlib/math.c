//
// Created by vinic on 07/09/18.
//

#include "math.h"
#include "../program_stack.h"
#include "../words.h"

#define TWO_OPERATOR(x) number_t n1, n2;\
POP_NUMBER(n1, stack);\
POP_NUMBER(n2, stack);\
PStack_push(stack, STACK_NUMBER(x));

static void math_add(ProgramStack stack) {
    TWO_OPERATOR(n1 + n2);
}

static void math_sub(ProgramStack stack) {
    TWO_OPERATOR(n1 - n2);
}

static void math_mul(ProgramStack stack) {
    TWO_OPERATOR(n1 * n2);
}

static void math_div(ProgramStack stack) {
    TWO_OPERATOR(n1 / n2);
}

static void math_less(ProgramStack stack) {
    TWO_OPERATOR(n1 < n2)
}

static void math_less_or_equals(ProgramStack stack) {
    TWO_OPERATOR(n1 <= n2)
}

static void math_greater(ProgramStack stack) {
    TWO_OPERATOR(n1 > n2)
}

static void math_greater_or_equals(ProgramStack stack) {
    TWO_OPERATOR(n1 >= n2)
}

static void math_equals(ProgramStack stack) {
    TWO_OPERATOR(n1 == n2)
}

static void math_not_equals(ProgramStack stack) {
    TWO_OPERATOR(n1 != n2)
}

static void math_inverse(ProgramStack stack) {
    number_t n1;
    POP_NUMBER(n1, stack);
    PStack_push(stack, STACK_NUMBER(!n1));
}

void RegisterMathWords() {
    struct WordEntry wordEntry[] = {
            {"+",  math_add},
            {"-",  math_sub},
            {"*",  math_mul},
            {"/",  math_div},
            {"<",  math_less},
            {"<=", math_less_or_equals},
            {">",  math_greater},
            {">=", math_greater_or_equals},
            {"=",  math_equals},
            {"!=", math_not_equals},
            {"!",  math_inverse},
    };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
}
