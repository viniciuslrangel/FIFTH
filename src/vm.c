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
    s->callStack = CallStack_new();
    s->state = VM_STATE_NORMAL;
    s->context = 0;
    s->jumpToContext = 0;
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

    if (vmState->instructionsLength == 0)
        return 0;

    unsigned long instructionCount = vmState->currentInstruction;
    vmState->currentInstruction = 0;

    vmState->stack = PStack_new();
    RegisterStdWords();

    struct ProgramOp op;
    while (
            (op = vmState->instructions[vmState->currentInstruction++]),
                    vmState->currentInstruction <= instructionCount
            ) {
        switch (vmState->state) {
            case VM_STATE_NORMAL: {
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
                                        .string = DString_copy(op.data.str)
                                }
                        });
                    }
                        break;
                    case OP_WORD_CALL: {
                        DString str = op.data.str;

                        if (DString_raw(str)[0] == ':') {
                            if (DString_length(str) < 2) {
                                FATAL("Invalid word name %s", DString_raw(str));
                            } else {
                                vmState->state = VM_STATE_REGISTERING_WORD;
                                vmState->customWord.startIndex = vmState->currentInstruction;
                                vmState->customWord.name = DString_substr(str, 1, -1);
                            }
                        } else if (DString_rawEquals(str, ";")) {
                            if (CallStack_hasNext(vmState->callStack)) {
                                vmState->currentInstruction = CallStack_pop(vmState->callStack);
                            } else {
                                FATAL("Cannot return");
                            }
                        } else if (DString_rawEquals(str, "IF")) {
                            vmState->jumpToContext = vmState->context++;
                            bool t = false;
                            struct PElement bData = PStack_pop(vmState->stack);
                            if (bData.type == DATATYPE_NUMBER) {
                                t = bData.data.number != 0;
                            } else if (bData.type == DATATYPE_STRING) {
                                t = DString_length(bData.data.string) != 0;
                            }
                            if (!t) {
                                vmState->state = VM_STATE_JUMPING;
                            }
                        } else if (DString_rawEquals(str, "THEN")) {
                            if (vmState->context == 0) {
                                FATAL("Unbalanced IF/THEN");
                            }
                            vmState->context--;
                        } else {
                            struct FindWordResult r = FindWordByName(DString_raw(str));
                            if (r.native) {
                                CHECK_NOT_NULL(r.data.native, "Invalid word");
                                r.data.native(vmState, vmState->stack);
                            } else {
                                CallStack_push(vmState->callStack, vmState->currentInstruction);
                                vmState->currentInstruction = r.data.startIndex;
                            }
                        }
                    }
                }
            }
                break;
            case VM_STATE_REGISTERING_WORD: {
                if (op.op == OP_WORD_CALL) {
                    if (DString_raw(op.data.str)[0] == ':') {
                        FATAL("Cannot make inner words");
                    } else if (DString_rawEquals(op.data.str, ";")) {
                        RegisterCustomWords((struct CustomWordEntry) {
                                .name = vmState->customWord.name,
                                .startIndex = vmState->customWord.startIndex
                        });
                        vmState->state = VM_STATE_NORMAL;
                        break;
                    }
                }
                if (vmState->currentInstruction == instructionCount) {
                    FATAL("Unfinished word");
                }
            }
                break;
            case VM_STATE_JUMPING: {
                if (op.op == OP_WORD_CALL) {
                    if (DString_rawEquals(op.data.str, "IF")) {
                        vmState->context++;
                        break;
                    } else if (DString_rawEquals(op.data.str, "THEN") &&
                               --vmState->context == vmState->jumpToContext) {
                        vmState->state = VM_STATE_NORMAL;
                        break;
                    }
                }
                if (vmState->currentInstruction == instructionCount) {
                    FATAL("Unfinished IF");
                }
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
