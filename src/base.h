//
// Created by vinic on 04/09/18.
//

#ifndef FIFTH_CONST_H
#define FIFTH_CONST_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define __MACRO_FUNCTION_BODY(x) do { x } while(0)

#define _OUT_ // Use this to mark parameter as output

//region Constants

#define NAME FIFTH FIFTH
#define NAME_STR "FIFTH"

#define MAJOR_VERSION 0
#define MINOR_VERSION 4
#define PATCH_VERSION 0

#ifndef NULL
#define NULL (void*)0
#endif

#ifndef _FIFTH_TEST
#include "runtime_impl.h"
#else
#include "../test/test_impl.h"
#endif

#define bool int8_t
#define true ((int8_t )1)
#define false ((int8_t )0)

#define number_t double

//endregion

//region Logger

#define FPRINT(x, y, ...) fprintf(x, y, ##__VA_ARGS__)

#define PRINT(x, ...) FPRINT(stdout, x, ##__VA_ARGS__)
#define PRINTLN(x, ...) __MACRO_FUNCTION_BODY( PRINT(x, ___VA_ARGS___); PRINT("\n"); )

#define ERROR(x, ...) FPRINT(stderr, x, ##__VA_ARGS__)
#define ERRORLN(x, ...) __MACRO_FUNCTION_BODY( ERROR(x, ##__VA_ARGS__); ERROR("\n"); )

#define FATAL(x, ...) __MACRO_FUNCTION_BODY( fflush(stdout); ERRORLN(x, ##__VA_ARGS__); exit(1); )

//region Debug

#ifdef _FIFTH_DEBUG
#define DEBUG(x, ...) FPRINT(stdout, x, ##__VA_ARGS__)  
#define DEBUGLN(x, ...) __MACRO_FUNCTION_BODY( DEBUG(x, __VA_ARGS__); PRINT("\n"); )
#else
#define DEBUG(...) __MACRO_FUNCTION_BODY()
#define DEBUGLN(...) __MACRO_FUNCTION_BODY()
#endif

//endregion

//endregion


//region Utility

#define ASSERT(x, y, ...) __MACRO_FUNCTION_BODY( if (!(x)) FATAL(y, ##__VA_ARGS__); )
#define CHECK_NOT_NULL(x, y, ...) ASSERT((x) != NULL, y, ##__VA_ARGS__)

#define UPPER(x) ((char)('a' <= (x) && (x) <= 'z' ? (x) + 'A' - 'a' : (x)))

/**
 * Converts any expression in true/false value
 */
#define BOOL(x) (x) ? true : false

//endregion

#endif //FIFTH_CONST_H
