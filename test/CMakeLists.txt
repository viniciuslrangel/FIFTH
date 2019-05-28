set(ENABLE_TESTING_UNIT false CACHE BOOL "Enables testing unit")

if (${ENABLE_TESTING_UNIT})

    include_directories(
            "${PROJECT_SOURCE_DIR}/src"
    )

    enable_testing()
    if(WIN32)
        find_library(CMOCKA_LIBRARY libcmocka.dll.a)
    else()
        find_library(CMOCKA_LIBRARY libcmocka.so.0)
    endif()

    if (CMOCKA_LIBRARY)
        add_executable(fifth_test
                test.c
                test_dynamic_string.c
                ../src/dynamic_string.c
                test_impl.h)
        target_link_libraries(fifth_test ${CMOCKA_LIBRARY})
        add_test(fifth_test test)

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FIFTH_TEST")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_FIFTH_DEBUG")
    else ()
        message(FATAL_ERROR "Unit Testing enabled but cmocka library was not found")
    endif ()

endif ()