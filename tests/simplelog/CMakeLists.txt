# ===========================================================================
# CMAKE: cxx.simplelog/tests/simplelog.backend.spdlog
# ===========================================================================
# Build test program(s) with C++ doctest and test it
# SEE ALSO: https://rix0r.nl/blog/2015/08/13/cmake-guide/

# ---------------------------------------------------------------------------
# EXECUTABLES:
# ---------------------------------------------------------------------------
# SEE: https://github.com/onqtam/doctest
add_executable(test_simplelog)
target_sources(test_simplelog
    PRIVATE
        test_main.cpp
        test_backend.cpp
        test_LogMacros.cpp
)
target_link_libraries(test_simplelog
    cxx_simplelog::simplelog_spdlog
    doctest::doctest
)
target_include_directories(test_simplelog
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../.."
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_compile_definitions(test_simplelog
    PRIVATE
        ${SIMPLELOG_TEST__COMMON_CXX_COMPILE_DEFINITIONS}
)

# ---------------------------------------------------------------------------
# -- AUTO-RUN TESTS:
# ---------------------------------------------------------------------------
# AND: Always build test-programs.
# set(BUILD_TESTING ON)

# -- SOLUTION 1: Builds other programs, libs first. Then runs tests.
# add_custom_target(tests2 ALL
#    COMMAND ctest
#    DEPENDS test_doctest1
#    COMMENT "AUTO-RUN TESTS with: all")

# -- SOLUTION 2: Build program, then run test(s) with it.
# add_custom_command(TARGET hello_app POST_BUILD
#         COMMAND ctest
#         COMMENT "AUTO-RUN TESTS (after build-step)")
# ---------------------------------------------------------------------------
# SECTION: Tests
# ---------------------------------------------------------------------------
add_test(NAME test_simplelog
    COMMAND test_simplelog -s
)
# set_tests_properties(test_all PROPERTIES
#   PASS_REGULAR_EXPRESSION     "1 test cases out of 1 passed")
# HINT: set_tests_properties() above captures and verifies output against expectations.

