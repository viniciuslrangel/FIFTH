//
// Created by vinic on 06/09/18.
//

#ifndef FIFTH_VM_H
#define FIFTH_VM_H

#include "base.h"
#include "program_stack.h"
#include "dynamic_string.h"

enum OpCode {
    OP_NOP,
    OP_PUSH_N,
    OP_PUSH_S,
    OP_WORD_CALL
};

typedef void(*WordCall)(ProgramStack);

struct ProgramOp {
    enum OpCode op;
    union {
        number_t number;
        DString str;
    } data;
};

typedef struct ___VmState {
    struct ProgramOp *instructions;
    unsigned long instructionsLength;
    unsigned long currentInstruction;
    ProgramStack stack;
} *VmState;

VmState CreateVm();

void InsertInstruction(VmState, struct ProgramOp);

number_t RunVm(VmState vmState);

#endif //FIFTH_VM_H
