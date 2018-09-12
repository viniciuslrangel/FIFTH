include_directories(
        "${PROJECT_SOURCE_DIR}/src"
)

enable_testing()
find_library(CMOCKA_LIBRARY libcmocka.so.0)

add_executable(fifth_test
        test.c
        test_dynamic_string.c
        ../src/dynamic_string.c
        test_impl.h)
target_link_libraries(fifth_test ${CMOCKA_LIBRARY})
add_test(fifth_test test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FIFTH_TEST")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_FIFTH_DEBUG")