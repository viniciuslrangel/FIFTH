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

#define FUNC(x) static void x(VmState vm, ProgramStack stack)

FUNC(math_add) {
    TWO_OPERATOR(n1 + n2);
}

FUNC(math_sub) {
    TWO_OPERATOR(n1 - n2);
}

FUNC(math_mul) {
    TWO_OPERATOR(n1 * n2);
}

FUNC(math_div) {
    TWO_OPERATOR(n1 / n2);
}

FUNC(math_less) {
    TWO_OPERATOR(n1 < n2)
}

FUNC(math_less_or_equals) {
    TWO_OPERATOR(n1 <= n2)
}

FUNC(math_greater) {
    TWO_OPERATOR(n1 > n2)
}

FUNC(math_greater_or_equals) {
    TWO_OPERATOR(n1 >= n2)
}

FUNC(math_equals) {
    TWO_OPERATOR(n1 == n2)
}

FUNC(math_not_equals) {
    TWO_OPERATOR(n1 != n2)
}

FUNC(math_inverse) {
    number_t n1;
    POP_NUMBER(n1, stack);
    PStack_push(stack, STACK_NUMBER(!n1));
}

FUNC(math_logic_or) {
    TWO_OPERATOR(n1 || n2)
}

FUNC(math_logic_and) {
    TWO_OPERATOR(n1 && n2)
}

FUNC(math_logic_xor) {
    TWO_OPERATOR((int) n1 ^ (int) n2)
}

#undef FUNC

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
            {"||",  math_logic_or},
            {"&&",  math_logic_and},
            {"^^",  math_logic_xor}
    };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
}
