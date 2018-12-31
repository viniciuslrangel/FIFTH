//
// Created by vinic on 07/09/18.
//

#include <errno.h>
#include <stdlib.h>
#include "std_words.h"
#include "math.h"
#include "string.h"
#include "../program_stack.h"
#include "../words.h"

#define FUNC(x) static void x(VmState vm, ProgramStack stack)

FUNC(stdlib_read) {
    DString str = DString_new("");
    char c;
    while((c = (char) getc(stdin)) != '\n' && c != ' ' && c != 0) {
        DString_appendChar(str, c);
    }
    PStack_push(stack, STACK_STR(str));
}

FUNC(stdlib_readln) {
    DString str = DString_new("");
    char c;
    while((c = (char) getc(stdin)) != '\n' && c != 0) {
        DString_appendChar(str, c);
    }
    PStack_push(stack, STACK_STR(str));
}

FUNC(stdlib_readnum) {
    char num[60];
    scanf("%s", num);
    char *err;
    number_t data = strtod(num, &err);
    if(*err != '\0'){
        PStack_push(stack, STACK_STR(DString_new("NaN")));
    } else {
        PStack_push(stack, STACK_NUMBER(data));
    }

}

FUNC(stdlib_print) {
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

FUNC(stdlib_println) {
    stdlib_print(vm, stack);
    putchar('\n');
}

FUNC(stdlib_dup) {
    struct PElement e = PStack_peek(stack);
    if(e.type == DATATYPE_STRING) {
        e.data.string = DString_copy(e.data.string);
    }
    PStack_push(stack, e);
}

FUNC(stdlib_ddup) {
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

FUNC(stdlib_switch) {
    struct PElement e1 = PStack_pop(stack);
    struct PElement e2 = PStack_pop(stack);
    PStack_push(stack, e1);
    PStack_push(stack, e2);
}

FUNC(stdlib_tonum) {
    struct PElement e = PStack_pop(stack);
    switch (e.type) {
        case DATATYPE_NUMBER:
            PStack_push(stack, e);
            break;
        case DATATYPE_STRING: {
            char *err;
            double r = strtod(DString_raw(e.data.string), &err);
            if(err != NULL) {
                PStack_push(stack, STACK_STR(DString_new("ERR")));
            } else if(errno == ERANGE) {
                PStack_push(stack, STACK_STR(DString_new("OVERFLOW")));
            } else {
                PStack_push(stack, STACK_NUMBER(r));
                DString_delete(e.data.string);
            }
        }
            break;
        default:
            FATAL("Stack corruption");
    }
}

FUNC(stdlib_nswitch) {
    number_t index;
    POP_NUMBER(index, stack);

    struct PElement e1 = PStack_popIndex(stack, (unsigned int) index);
    struct PElement e2 = PStack_pop(stack);
    PStack_push(stack, e1);
    PStack_pushIndex(stack, e2, (unsigned int) index);
}

FUNC(stdlib_nnswitch) {
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

FUNC(stdlib_call) {
    struct PElement e = PStack_pop(stack);
    if(e.type != DATATYPE_STRING) {
        FATAL("Call argument must be string");
    }
    struct FindWordResult r = FindWordByName(DString_raw(DString_toUpperCase(e.data.string)));
    DString_delete(e.data.string);
    if (r.native) {
        CHECK_NOT_NULL(r.data.native, "Invalid word");
        r.data.native(vm, stack);
    } else {
        CallStack_push(vm->callStack, vm->currentInstruction);
        vm->currentInstruction = r.data.startIndex;
    }
}

FUNC(stdlib_length) {
    PStack_push(stack, STACK_NUMBER(PStack_length(stack)));
}

#undef FUNC

void RegisterStdWords() {
    struct WordEntry wordEntry[] = {
                {"READ", stdlib_read},
                {"READLN", stdlib_readln},
                {"READNUM", stdlib_readnum},
                {"PRINT", stdlib_print},
                {"PRINTLN", stdlib_println},
                {"DUP", stdlib_dup},
                {"DDUP", stdlib_ddup},
                {"SWITCH", stdlib_switch},
                {"NSWITCH", stdlib_nswitch},
                {"NNSWITCH", stdlib_nnswitch},
                {"TONUM", stdlib_tonum},
                {"CALL", stdlib_call},
                {"LENGTH", stdlib_length}
        };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
    RegisterMathWords();
}
