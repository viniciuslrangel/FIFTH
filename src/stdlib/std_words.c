//
// Created by vinic on 07/09/18.
//

#include "std_words.h"
#include "math.h"
#include "string.h"
#include "../program_stack.h"
#include "../words.h"

static void stdlib_print(ProgramStack stack) {
    struct PElement ele = PStack_pop(stack);
    switch (ele.type) {
        case DATATYPE_STRING:
            fputs(DString_raw(ele.data.string), stdout);
            DString_delete(ele.data.string);
            break;
        case DATATYPE_NUMBER:
            printf("%lf", ele.data.number);
            break;
        default:
            puts("Corrupted stack\n");
    }
}

static void stdlib_println(ProgramStack stack) {
    stdlib_print(stack);
    putchar('\n');
}

static void stdlib_dup(ProgramStack stack) {
    struct PElement e = PStack_peek(stack);
    if(e.type == DATATYPE_STRING) {
        e.data.string = DString_copy(e.data.string);
    }
    PStack_push(stack, e);
}

static void stdlib_ddup(ProgramStack stack) {
    struct PElement e1 = PStack_peekIndex(stack, 0);
    struct PElement e2 = PStack_peekIndex(stack, 1);
    if(e1.type == DATATYPE_STRING) {
        e1.data.string = DString_copy(e1.data.string);
    }
    if(e2.type == DATATYPE_STRING) {
        e2.data.string = DString_copy(e2.data.string);
    }
    PStack_push(stack, e2);
    PStack_push(stack, e1);
}

static void stdlib_switch(ProgramStack stack) {
    struct PElement e1 = PStack_pop(stack);
    struct PElement e2 = PStack_pop(stack);
    PStack_push(stack, e1);
    PStack_push(stack, e2);
}

static void stdlib_tonum(ProgramStack stack) {
    struct PElement e = PStack_pop(stack);
    switch (e.type) {
        case DATATYPE_NUMBER:
            PStack_push(stack, e);
            break;
        case DATATYPE_STRING:
            PStack_push(stack, STACK_NUMBER(strtod(DString_raw(e.data.string), NULL)));
            DString_delete(e.data.string);
            break;
        default:
            FATAL("Stack corruption");
    }
}

static void stdlib_nswitch(ProgramStack stack) {
    number_t index;
    POP_NUMBER(index, stack);

    struct PElement e1 = PStack_popIndex(stack, (unsigned int) index);
    struct PElement e2 = PStack_pop(stack);
    PStack_push(stack, e1);
    PStack_pushIndex(stack, e2, (unsigned int) index);
}

static void stdlib_nnswitch(ProgramStack stack) {
    number_t i1, i2;
    POP_NUMBER(i1, stack);
    POP_NUMBER(i2, stack);
    if(i1 < i2) {
        number_t tmp = i1;
        i1 = i2;
        i2 = tmp;
    }

    struct PElement e1 = PStack_popIndex(stack, (unsigned int) i1);
    struct PElement e2 = PStack_popIndex(stack, (unsigned int) i2);
    PStack_pushIndex(stack, e1, (unsigned int) i2);
    PStack_pushIndex(stack, e2, (unsigned int) i1);
}

void RegisterStdWords() {
    struct WordEntry wordEntry[] = {
                {"PRINT", stdlib_print},
                {"PRINTLN", stdlib_println},
                {"DUP", stdlib_dup},
                {"DDUP", stdlib_ddup},
                {"SWITCH", stdlib_switch},
                {"NSWITCH", stdlib_nswitch},
                {"NNSWITCH", stdlib_nnswitch},
                {"TONUM", stdlib_tonum}
        };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
    RegisterMathWords();
}
