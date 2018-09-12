//
// Created by viniciuslrangel on 12/09/18.
//
#include "base.h"
#include "test.h"

#define malloc(x) test_malloc(x)
#define realloc(x, y) test_realloc(x, y)
#define calloc(x, y) test_calloc(x, y)
#define free(x) test_free(x)