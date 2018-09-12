//
// Created by viniciuslrangel on 12/09/18.
//

#ifndef FIFTH_CALL_STACK_H
#define FIFTH_CALL_STACK_H

#include "base.h"

typedef struct ___CallStack *CallStack;

CallStack CallStack_new();

void CallStack_push(CallStack, unsigned long);

unsigned long CallStack_pop(CallStack);

bool CallStack_hasNext(CallStack);

#endif //FIFTH_CALL_STACK_H
