//
// Created by vinic on 06/09/18.
//

#include "program_stack.h"

struct ProgramNode {
    enum DataType type;
    union PData data;
    struct ProgramNode *bottom;
};

struct __ProgramStack {
    struct ProgramNode *node;
    unsigned int length;
};

ProgramStack PStack_new() {
    struct __ProgramStack *s = malloc(sizeof(struct __ProgramStack));
    s->node = NULL;
    s->length = 0;
    return s;
}

struct PElement PStack_pop(ProgramStack stack) {
    if (stack->length == 0) {
        FATAL("Stack empty");
    }
    stack->length--;
    struct ProgramNode *node = stack->node;
    stack->node = node->bottom;
    struct PElement elem = {
            node->type,
            node->data
    };
    free(node);
    return elem;
}

void PStack_push(ProgramStack stack, struct PElement in) {
    stack->length++;
    struct ProgramNode *node = malloc(sizeof(struct ProgramNode));
    node->type = in.type;
    node->data = in.data;
    node->bottom = stack->node;
    stack->node = node;
}

unsigned int PStack_length(ProgramStack stack) {
    return stack->length;
}

void PStack_delete(ProgramStack stack) {
    while (stack->node != NULL) {
        struct ProgramNode *node = stack->node;
        stack->node = node->bottom;
        free(node);
    }
    free(stack);
}