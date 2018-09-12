//
// Created by vinic on 06/09/18.
//

#include "vm.h"
#include "program_stack.h"
#include "words.h"
#include "stdlib/std_words.h"

VmState CreateVm() {
    VmState s = malloc(sizeof(struct ___VmState));
    s->instructionsLength = 10;
    s->instructions = malloc(sizeof(struct ProgramOp) * s->instructionsLength);
    s->currentInstruction = 0;
    s->stack = NULL;
    return s;
}

void InsertInstruction(VmState state, struct ProgramOp op) {
    if (state->currentInstruction >= state->instructionsLength) {
        state->instructionsLength = (unsigned long) (state->instructionsLength * 1.5);
        CHECK_NOT_NULL(
                state->instructions = realloc(state->instructions,
                                              sizeof(struct ProgramOp) * state->instructionsLength),
                "Cannot allocate memory for storing the program instructions"
        );
    }
    state->instructions[state->currentInstruction++] = op;
}

number_t RunVm(VmState vmState) {

    if(vmState->instructionsLength == 0)
        return 0;

    vmState->currentInstruction = 0;
    vmState->stack = PStack_new();
    RegisterStdWords();

    struct ProgramOp op;
    while ((op = vmState->instructions[vmState->currentInstruction++]), vmState->currentInstruction <= vmState->instructionsLength) {

        switch (op.op) {
            case OP_NOP:
                break;
            case OP_PUSH_N: {
                PStack_push(vmState->stack, (struct PElement) {
                        .type = DATATYPE_NUMBER,
                        .data = {
                                .number = op.data.number
                        }
                });
            }
                break;
            case OP_PUSH_S: {
                PStack_push(vmState->stack, (struct PElement) {
                        .type = DATATYPE_STRING,
                        .data = {
                                .string = DString_raw(op.data.str)
                        }
                });
            }
                break;
            case OP_WORD_CALL: {
                WordCall word = FindWordByName(DString_raw(op.data.str));
                CHECK_NOT_NULL(word, "Invalid word");
                word(vmState->stack);
            }
        }
    }
    number_t result = 0;
    if (PStack_length(vmState->stack) > 0) {
        struct PElement e = PStack_pop(vmState->stack);
        if (e.type == DATATYPE_NUMBER) {
            result = e.data.number;
        } else {
            free(e.data.string);
        }
    }
    PStack_delete(vmState->stack);
    return result;
}
