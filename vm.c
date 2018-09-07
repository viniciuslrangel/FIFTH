//
// Created by vinic on 06/09/18.
//

#include "vm.h"
#include "program_stack.h"
#include "words.h"
#include "stdlib/std_words.h"

struct InstructionStack {
    struct ProgramOp op;
    struct InstructionStack *next;
};

struct {
    struct InstructionStack *firstInstruction;
    struct InstructionStack *lastInstruction;
    struct InstructionStack *currentExecuting;
    ProgramStack stack;
    int line;
} VmState = {NULL, NULL, NULL, 0};

void InsertInstruction(struct ProgramOp op) {
    struct InstructionStack *newStack = malloc(sizeof(struct InstructionStack));
    if(!newStack) {
        FATAL("Cannot allocate memory");
    }
    newStack->op = op;
    if (VmState.firstInstruction == NULL) {
        VmState.firstInstruction = newStack;
    }
    if (VmState.lastInstruction != NULL) {
        VmState.lastInstruction->next = newStack;
    }
    VmState.lastInstruction = newStack;
}

number_t RunVm() {
    VmState.stack = PStack_new();
    RegisterStdWords();

    VmState.currentExecuting = VmState.firstInstruction;

    struct InstructionStack *current;
    while ((current = VmState.currentExecuting) != NULL) {

        struct ProgramOp op = current->op;
        switch (op.op) {
            case OP_NOP:
                break;
            case OP_PUSH_N: {
                PStack_push(VmState.stack, (struct PElement) {
                        .type = DATATYPE_NUMBER,
                        .data = {
                                .number = op.data.number
                        }
                });
            }
                break;
            case OP_PUSH_S: {
                PStack_push(VmState.stack, (struct PElement) {
                        .type = DATATYPE_STRING,
                        .data = {
                                .string = op.data.str
                        }
                });
            }
                break;
            case OP_WORD_CALL: {
                WordCall word = FindWordByName(op.data.str);
                CHECK_NOT_NULL(word, "Invalid word");
                word(VmState.stack);
            }
        }
        VmState.currentExecuting = current->next;
        free(current);
    }
    number_t result = 0;
    if (PStack_length(VmState.stack) > 0) {
        struct PElement e = PStack_pop(VmState.stack);
        if (e.type == DATATYPE_NUMBER) {
            result = e.data.number;
        } else {
            free(e.data.string);
        }
    }
    PStack_delete(VmState.stack);
    return result;
}
