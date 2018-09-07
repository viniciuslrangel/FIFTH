//
// Created by vinic on 07/09/18.
//

#include "std_words.h"
#include "math.h"
#include "string.h"
#include "../program_stack.h"
#include "../words.h"

void stdlib_print(ProgramStack stack) {
    struct PElement ele = PStack_pop(stack);
    switch (ele.type) {
        case DATATYPE_STRING:
            fputs(ele.data.string, stdout);
            free(ele.data.string);
            break;
        case DATATYPE_NUMBER:
            printf("%lf", ele.data.number);
            break;
        default:
            puts("Corrupted stack\n");
    }
}

void stdlib_println(ProgramStack stack) {
    stdlib_print(stack);
    putchar('\n');
}

void stdlib_dup(ProgramStack stack) {
    struct PElement e = PStack_pop(stack);
    PStack_push(stack, e);
    if(e.type == DATATYPE_STRING) {
        char* copy = malloc(strlen(e.data.string) + 1);
        strcpy(copy, e.data.string);
        e.data.string = copy;
    }
    PStack_push(stack, e);
}

void stdlib_switch(ProgramStack stack) {
    struct PElement e1 = PStack_pop(stack);
    struct PElement e2 = PStack_pop(stack);
    PStack_push(stack, e1);
    PStack_push(stack, e2);
}

void stdlib_tonum(ProgramStack stack) {
    struct PElement e = PStack_pop(stack);
    switch (e.type) {
        case DATATYPE_NUMBER:
            PStack_push(stack, e);
            break;
        case DATATYPE_STRING:
            PStack_push(stack, STACK_NUMBER(strtod(e.data.string, NULL)));
            break;
        default:
            FATAL("Stack corruption");
    }
}

void RegisterStdWords() {
    struct WordEntry wordEntry[] = {
                {"PRINT", stdlib_print},
                {"PRINTLN", stdlib_println},
                {"DUP", stdlib_dup},
                {"SWITCH", stdlib_switch},
                {"TONUM", stdlib_tonum}
        };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
    RegisterMathWords();
}
