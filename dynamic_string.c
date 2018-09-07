//
// Created by vinic on 04/09/18.
//

#include "dynamic_string.h"
#include "base.h"
#include "string.h"

#define SIZE sizeof(char)

struct DString_Data {
    char *raw;
    int length;
};

DString DString_new() {
    struct DString_Data *s = malloc(sizeof(struct DString_Data));
    s->length = 0;
    s->raw = malloc(sizeof(char));
    s->raw[0] = 0;
    return s;
}

int DString_length(DString str) {
    return str->length;
}

void DString_appendChar(DString str, char c) {
    char* newStr = realloc(str->raw, SIZE * (++str->length + 1));
    if(newStr != NULL) {
        str->raw = newStr;
        str->raw[str->length - 1] = c;
        str->raw[str->length] = 0;
    }
}

char *DString_raw(DString str) {
    return str->raw;
}

void DString_clear(DString str) {
    if (str->length != 0) {
        realloc(str->raw, SIZE);
    }
    str->raw[0] = 0;
}

void DString_delete(DString str) {
    free(str->raw);
    free(str);
}

char *DString_copy(DString str) {
    char* c = malloc(SIZE * (str->length + 1));
    memcpy(c, str->raw, (size_t) (str->length + 1)); // NOLINT(bugprone-misplaced-widening-cast)
    return c;
}

#undef SIZE