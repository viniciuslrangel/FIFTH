//
// Created by vinic on 04/09/18.
//

#include "dynamic_string.h"
#include "base.h"
#include "string.h"

#define SIZE sizeof(char)

struct ___DString {
    char *raw;
    size_t length;
};

DString DString_new(char* str) {
    struct ___DString *s = malloc(sizeof(struct ___DString));
    size_t length = strlen(str);
    s->length = length;
    s->raw = malloc(length + 1);
    s->raw[length] = 0;
    return s;
}

int DString_length(DString str) {
    return str->length;
}

void DString_append(DString str, DString other) {
    CHECK_NOT_NULL(str->raw = realloc(str->raw, SIZE * (str->length + other->length + 1)), __func__);
    memcpy(str->raw + str->length, other->raw, (size_t) other->length);
    str->length += other->length;
    str->raw[str->length] = 0;
}

void DString_appendChar(DString str, char c) {
    CHECK_NOT_NULL(str->raw = realloc(str->raw, SIZE * (++str->length + 1)), __func__);
    str->raw[str->length - 1] = c;
    str->raw[str->length] = 0;
}

char *DString_raw(DString str) {
    return str->raw;
}

void DString_clear(DString str) {
    if (str->length != 0) {
        CHECK_NOT_NULL(str->raw = realloc(str->raw, SIZE), __func__);
    }
    str->raw[0] = 0;
}

void DString_delete(DString str) {
    free(str->raw);
    free(str);
}

DString DString_copy(DString str) {
    return DString_new(DString_raw(str));
}

#undef SIZE