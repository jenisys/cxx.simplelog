# ===========================================================================
# CMAKE: cxx.simplelog/tests/simplelog.backend.null
# ===========================================================================
# Build test program(s) with C++ doctest and test it
# SEE ALSO: https://rix0r.nl/blog/2015/08/13/cmake-guide/

# ---------------------------------------------------------------------------
# EXECUTABLES:
# ---------------------------------------------------------------------------
# SEE: https://github.com/onqtam/doctest
add_executable(test_simplelog_backend_null)
target_sources(
    test_simplelog_backend_null
    PRIVATE test_main.cpp
            test_LogMacros.cpp
            # -- COMPILE-CHECK:
            test_compilable.LogMacros.cpp
            test_compilable.LogMacros0.cpp
            test_compilable.TraceMacros.cpp
)
target_link_libraries(test_simplelog_backend_null cxx_simplelog::simplelog_null doctest::doctest)
target_compile_definitions(
    test_simplelog_backend_null PRIVATE ${SIMPLELOG_TEST__COMMON_CXX_COMPILE_DEFINITIONS}
)

# ---------------------------------------------------------------------------
# SECTION: Tests
# ---------------------------------------------------------------------------
add_test(NAME test_simplelog.backend.null COMMAND test_simplelog_backend_null -s)
