//
// Created by viniciuslrangel on 12/09/18.
//

#include "call_stack.h"

struct CallStackNode {
    unsigned long position;
    struct CallStackNode *next;
};

struct ___CallStack {
    struct CallStackNode *current;
};

CallStack CallStack_new() {
    CallStack cs = malloc(sizeof(struct ___CallStack));
    cs->current = NULL;
    return cs;
}

void CallStack_push(CallStack cs, unsigned long position) {
    struct CallStackNode *node = malloc(sizeof(struct CallStackNode));
    node->position = position;
    node->next = cs->current;
    cs->current = node;
}

unsigned long CallStack_pop(CallStack cs) {
    struct CallStackNode *node = cs->current;
    cs->current = node->next;
    unsigned long position = node->position;
    free(node);
    return position;
}

bool CallStack_hasNext(CallStack cs) {
    return (bool) (cs->current != NULL);
}
