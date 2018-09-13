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
    return PStack_popIndex(stack, 0);
}

struct PElement PStack_popIndex(ProgramStack stack, unsigned int index) {
    if (stack->length <= index) {
        FATAL("Stack out of bound");
    }
    stack->length--;
    struct ProgramNode *node = stack->node;
    if (index == 0) {
        stack->node = node->bottom;
    } else {
        for (unsigned int i = 1; i < index; ++i) {
            node = node->bottom;
        }
        struct ProgramNode *top = node;
        node = node->bottom;
        top->bottom = node->bottom;
    }
    struct PElement elem = {
            node->type,
            node->data
    };
    free(node);
    return elem;
}

struct PElement PStack_peek(ProgramStack stack) {
    return PStack_peekIndex(stack, 0);
}

struct PElement PStack_peekIndex(ProgramStack stack, unsigned int index) {
    if (stack->length <= index) {
        FATAL("Stack out of bound");
    }
    struct ProgramNode *node = stack->node;
    for (unsigned int i = 0; i < index; ++i) {
        node = node->bottom;
    }
    return (struct PElement) {
            node->type,
            node->data
    };
}

void PStack_push(ProgramStack stack, struct PElement in) {
    PStack_pushIndex(stack, in, 0);
	return;
}

void PStack_pushIndex(ProgramStack stack, struct PElement in, unsigned int index) {
    if (index > stack->length) {
        FATAL("Pushing value out bound of the stack");
    }
    stack->length++;
    struct ProgramNode *node = malloc(sizeof(struct ProgramNode));
    node->type = in.type;
    node->data = in.data;

    if (index == 0) {
        node->bottom = stack->node;
        stack->node = node;
    } else {
        struct ProgramNode *head = stack->node;
        for(unsigned int i = 1; i < index; ++i) {
            head = head->bottom;
        }
        struct ProgramNode *tmp = head->bottom;
        head->bottom = node;
        node->bottom = tmp;
    }
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
