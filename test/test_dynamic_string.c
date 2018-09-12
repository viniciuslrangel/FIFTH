//
// Created by viniciuslrangel on 11/09/18.
//

#include "test_dynamic_string.h"
#include "dynamic_string.h"

static int setup(DString **state) {
    *state = malloc(sizeof(DString) * 2);
    (*state)[0] = DString_new("foo_");
    (*state)[1] = DString_new("bar");
    return 0;
}

static int teardown(DString **state) {
    DString_delete((*state)[0]);
    DString_delete((*state)[1]);
    return 0;
}

static void test_new(DString **state) {
    (void) state;
    DString s = DString_new("foo");
    DString_delete(s);
}

static void test_create(DString **state) {
    (void) state;

    char *t = malloc(4);
    t[0] = 'f';
    t[1] = t[2] = 'o';
    t[3] = 0;
    DString s = DString_create(t);
    assert_string_equal(DString_raw(s), "foo");
    DString_delete(s);
}

static void test_length(DString **state) {
    assert_int_equal(DString_length((*state)[0]), 4);
}

static void test_char_append(DString **state) {
    DString boo = DString_copy((*state)[0]);
    DString_appendChar(boo, '2');
    assert_string_equal(DString_raw(boo), "foo_2");
    DString_delete(boo);
}

static void test_string_concat(DString **state) {
    DString boo = DString_copy((*state)[0]);
    DString_append(boo, (*state)[1]);
    assert_string_equal(DString_raw(boo), "foo_bar");
    DString_delete(boo);
}

static void test_string_clear(DString **state) {
    (void) state;

    DString s = DString_new("foo");
    DString_clear(s);
    assert_string_equal(DString_raw(s), "");
    assert_int_equal(DString_length(s), 0);
    DString_delete(s);
}

static void test_string_substr(DString **state) {
    DString s = DString_substr((*state)[0], 1, -2);
    assert_string_equal(DString_raw(s), "oo");
    DString_delete(s);

    s = DString_substr((*state)[0], -2, 1);
    assert_string_equal(DString_raw(s), "oo");
    DString_delete(s);

    s = DString_substr((*state)[1], 0, -2);
    assert_string_equal(DString_raw(s), "ba");
    DString_delete(s);
}

void test_dynamic_string() {

#define o(n) cmocka_unit_test((void(*)(void**))(n)),
    CMOCKA_TEST_GROUP(dynamic_string) = {
            o(test_new)
            o(test_create)
            o(test_length)
            o(test_char_append)
            o(test_string_concat)
            o(test_string_clear)
            o(test_string_substr)
    };
#undef o
    cmocka_run_group_tests_name(__func__, dynamic_string, setup, teardown);
}
