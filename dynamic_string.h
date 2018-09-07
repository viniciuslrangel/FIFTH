//
// Created by vinic on 04/09/18.
//

#ifndef FIRSTLANG_DYNAMIC_STRING_H
#define FIRSTLANG_DYNAMIC_STRING_H

#include <stdint-gcc.h>

typedef struct DString_Data *DString;

DString DString_new();

/**
 * @return The length with the string excluding null-terminated character
 */
int DString_length(DString);

void DString_appendChar(DString, char c);

char* DString_raw(DString);

void DString_clear(DString);

void DString_delete(DString);

char* DString_copy(DString);

#endif //FIRSTLANG_DYNAMIC_STRING_H
