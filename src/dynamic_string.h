//
// Created by vinic on 04/09/18.
//

#ifndef FIRSTLANG_DYNAMIC_STRING_H
#define FIRSTLANG_DYNAMIC_STRING_H

#include "base.h"

typedef struct ___DString *DString;

/**
 * Create new DString
 * @param str Null-terminated string
 * @return A new DString storing str copy
 */
DString DString_new(char* str);

/**
 * Create new DString without copying the @param str
 * Do not free @param str by yourself
 * @param str Dynamic allocated string
 * @return A new DString storing a str (not a copy)
 */
DString DString_create(char* str);

/**
 * @return The length with the string excluding null-terminated character
 */
size_t DString_length(DString);

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

/**
 * Clear DString content and set length to 0
 */
void DString_clear(DString);

/**
 * Free the DString itself and its content
 */
void DString_delete(DString);

/**
 * @return A copy of DString with the same duplicated content
 */
DString DString_copy(DString);

/**
 * Get a substring copy
 * Greater or equals to 0, start counting from start
 * Less than 0 start counting from end (i.e. -1 is the last character)
 * If begin absolute character is greater than end, the parameters are switched
 * @param begin Begin character
 * @param end End character
 * @return DString copy
 */
DString DString_substr(DString, int begin, int end);

/**
 * Compares two DString
 * @return true if both two are equals
 * @see DString_rawEquals
 */
bool DString_equals(DString, DString);

/**
 * Compares two DString ignoring case
 * @return true if both two are equals
 * @see DString_rawEqualsIgnoreCase
 */
bool DString_equalsIgnoreCase(DString, DString);

/**
 * Compares DString with raw char sequence
 * @return true if both two are equals
 * @see DString_equals
 */
bool DString_rawEquals(DString, char*);

/**
 * Compares DString with raw char sequence ignoring case
 * @return true if both two are equals
 * @see DString_equalsIgnoreCase
 */
bool DString_rawEqualsIgnoreCase(DString, char*);

/**
 * Returns <b>not a copy</b> of the DString in upper case
 * @return the same DString
 */
DString DString_toUpperCase(DString);

#endif //FIRSTLANG_DYNAMIC_STRING_H
