//
// Created by viniciuslrangel on 11/09/18.
//

#include "test_dynamic_string.h"
#include "dynamic_string.h"

static DString foo;
static DString bar;

static int setup() {
    foo = DString_new("foo_");
    bar = DString_new("bar");
    return 0;
}

static int teardown() {
    DString_delete(foo);
    DString_delete(bar);
    return 0;
}

static void test_length() {
    assert_int_equal(DString_length(foo), 4);
}

static void test_char_append() {
    DString boo = DString_copy(foo);
    DString_appendChar(boo, '2');
    assert_string_equal(DString_raw(boo), "foo_2");
    DString_delete(boo);
}

static void test_string_concat() {
    DString boo = DString_copy(foo);
    DString_append(boo, bar);
    assert_string_equal(DString_raw(boo), "foo_bar");
    DString_delete(boo);
}

void test_dynamic_string() {

#define o(n) cmocka_unit_test(n),
    CMOCKA_TEST_GROUP(dynamic_string) = {
            o(test_length)
            o(test_char_append)
            o(test_string_concat)
    };
#undef o
    cmocka_run_group_tests_name(__func__, dynamic_string, setup, teardown);
}
