# ===========================================================================
# CMAKE: cxx.simplelog/examples
# ===========================================================================

cmake_minimum_required(VERSION 3.14...3.20)

# ---------------------------------------------------------------------------
# PROJECT:
# ---------------------------------------------------------------------------
project(cxx.simplelog.test LANGUAGES CXX)

set(MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT ON)

    list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
    include(ccache)
    include(cxx.setup_project)

    find_package(simplelog COMPONENTS null spdlog syslog)
endif()

# ---------------------------------------------------------------------------
# SECTION: EXECUTABLES
# ---------------------------------------------------------------------------
add_executable(simplelog_example_spdlog)
target_sources(simplelog_example_spdlog PRIVATE main.example_spdlog.cpp)
target_link_libraries(
    simplelog_example_spdlog
    PRIVATE simplelog::simplelog_spdlog # INHERITED: spdlog::spdlog
            # PREPARED: fmt::fmt
)
target_compile_options(
    simplelog_example_spdlog PRIVATE -Wall -Wextra -Wpedantic
)
target_compile_definitions(
    simplelog_example_spdlog PRIVATE SIMPLELOG_USE_BACKEND_SPDLOG=1
                                     SIMPLELOG_DIAG=1
)

add_executable(simplelog_example_null)
target_sources(simplelog_example_null PRIVATE main.example_null.cpp)
target_link_libraries(simplelog_example_null PRIVATE simplelog::simplelog_null)
target_compile_options(simplelog_example_null PRIVATE -Wall -Wextra -Wpedantic)
target_compile_definitions(
    simplelog_example_null PRIVATE # NOT-NEEDED: SIMPLELOG_USE_BACKEND_NULL=1
                                   SIMPLELOG_DIAG=1
)

if(TARGET simplelog::simplelog_syslog)
    add_executable(simplelog_example_syslog)
    target_sources(simplelog_example_syslog PRIVATE main.example_syslog.cpp)
    target_link_libraries(
        simplelog_example_syslog PRIVATE simplelog::simplelog_syslog
                                         # INHERITED: fmt::fmt
    )
    target_compile_options(
        simplelog_example_syslog PRIVATE -Wall -Wextra -Wpedantic
    )
    target_compile_definitions(
        simplelog_example_syslog
        PRIVATE SIMPLELOG_DIAG=1
                # INHERITED: SIMPLELOG_USE_BACKEND_SYSLOG=1
    )
endif()

# -- EXECUTABLE:
add_executable(example_variadic_args)
target_sources(
    example_variadic_args PRIVATE main.variadic_args_recipe_for_zero_args.cpp
)
target_link_libraries(example_variadic_args fmt::fmt)

### if(SIMPLELOG_USE_BUNDLED_FMTLIB)
###     target_compile_definitions(example_variadic_args PRIVATE SIMPLELOG_DIAG_USE_SPDLOG_FMTLIB=0)
### endif()

# ---------------------------------------------------------------------------
# SECTION: AUTO-RUN PROGRAMS
# ---------------------------------------------------------------------------
enable_testing()

set(EXAMPLE_PROGRAMS simplelog_example_spdlog simplelog_example_null
                     example_variadic_args
)
if(TARGET simplelog::simplelog_syslog)
    list(APPEND EXAMPLE_PROGRAMS simplelog_example_syslog)
endif()

add_custom_target(
    examples
    DEPENDS ${EXAMPLE_PROGRAMS}
    COMMENT "RUN: examples"
)

foreach(_EXAMPLE_PROGRAM ${EXAMPLE_PROGRAMS})
    add_test(NAME ${_EXAMPLE_PROGRAM} COMMAND ${_EXAMPLE_PROGRAM})
    add_custom_target(
        "run.${_EXAMPLE_PROGRAM}"
        COMMAND ${_EXAMPLE_PROGRAM}
        DEPENDS ${_EXAMPLE_PROGRAM}
        COMMENT "RUN: ${_EXAMPLE_PROGRAM}"
    )
endforeach()

# ---------------------------------------------------------------------------
# SECTION: Run examples as tests
# ---------------------------------------------------------------------------

# -- SOLUTION 1: Builds other programs, libs first
add_custom_target(
    test_examples ALL
    COMMAND ctest
    DEPENDS ${EXAMPLE_PROGRAMS}
    COMMENT "AUTO-RUN EXAMPLES with: all"
)

# -- more TESTS:
add_test(NAME example_simplelog.spdlog COMMAND simplelog_example_spdlog)
set_tests_properties(
    example_simplelog.spdlog
    PROPERTIES PASS_REGULAR_EXPRESSION ".*foo.bar::info.*  Hello Alice and Bob"
)

add_test(NAME example_simplelog.null COMMAND simplelog_example_null)
set_tests_properties(
    example_simplelog.null PROPERTIES PASS_REGULAR_EXPRESSION
                                      "NULL-EXAMPLE: Finished."
)
