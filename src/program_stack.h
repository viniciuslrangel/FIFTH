//
// Created by vinic on 06/09/18.
//

#ifndef FIFTH_PROGRAM_STACK_H
#define FIFTH_PROGRAM_STACK_H

#include "base.h"
#include "dynamic_string.h"

enum DataType {
    DATATYPE_NUMBER,
    DATATYPE_STRING
};

union PData {
    number_t number;
    DString string;
};

struct PElement {
    enum DataType type;
    union PData data;
};

typedef struct __ProgramStack *ProgramStack;

ProgramStack PStack_new();

struct PElement PStack_pop(ProgramStack stack);

struct PElement PStack_popIndex(ProgramStack stack, unsigned int index);

struct PElement PStack_peek(ProgramStack stack);

struct PElement PStack_peekIndex(ProgramStack stack, unsigned int index);

#define STACK_NUMBER(x) (struct PElement) {\
    .type = DATATYPE_NUMBER,\
    .data = {\
        .number = (x)\
    }\
}

#define STACK_STR(x) (struct PElement) {\
    .type = DATATYPE_STRING,\
    .data = {\
        .string = (x)\
    }\
}

#define POP_NUMBER(x, y) __MACRO_FUNCTION_BODY( struct PElement e = PStack_pop(y); if (e.type != DATATYPE_NUMBER) FATAL("Number is required"); (x) = e.data.number; )
#define POP_STRING(x, y) __MACRO_FUNCTION_BODY( struct PElement e = PStack_pop(y); if (e.type != DATATYPE_STRING) FATAL("Number is required"); (x) = e.data.string; )

void PStack_push(ProgramStack stack, struct PElement in);

void PStack_pushIndex(ProgramStack stack, struct PElement in, unsigned int index);

unsigned int PStack_length(ProgramStack stack);

void PStack_delete(ProgramStack stack);

#endif //FIFTH_PROGRAM_STACK_H
