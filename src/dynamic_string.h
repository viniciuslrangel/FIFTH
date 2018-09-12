//
// Created by vinic on 04/09/18.
//

#ifndef FIRSTLANG_DYNAMIC_STRING_H
#define FIRSTLANG_DYNAMIC_STRING_H

typedef struct ___DString *DString;

/**
 * Create new DString
 * @param str Null-terminated string
 * @return A new DString storing str as value
 */
DString DString_new(char* str);

/**
 * @return The length with the string excluding null-terminated character
 */
int DString_length(DString);

/**
 * Append string from second to first
 */
void DString_append(DString str, DString other);

/**
 * Append a character to DString
 */
void DString_appendChar(DString, char c);

/**
 * @return Internal char* pointer, do not free by yousoelf, use #{DString_delete}
 * @see DString_delete
 */
char* DString_raw(DString);

void DString_clear(DString);

void DString_delete(DString);

DString DString_copy(DString);

#endif //FIRSTLANG_DYNAMIC_STRING_H
