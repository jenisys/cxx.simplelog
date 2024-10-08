# ===========================================================================
# CMAKE: cxx.simplelog/examples
# ===========================================================================


# ---------------------------------------------------------------------------
# SECTION: EXECUTABLES
# ---------------------------------------------------------------------------
add_executable(simplelog_example_spdlog)
target_sources(simplelog_example_spdlog PRIVATE
    main.example_spdlog.cpp
)
target_link_libraries(simplelog_example_spdlog
    PRIVATE
        cxx_simplelog::simplelog_spdlog
        # PREPARED: fmt::fmt
)
target_include_directories(simplelog_example_spdlog
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_options(simplelog_example_spdlog
    PRIVATE  -Wall -Wpedantic
)
target_compile_definitions(simplelog_example_spdlog
    PRIVATE
        SIMPLELOG_USE_BACKEND_SPDLOG=1
        SIMPLELOG_DIAG=1
)

# -- EXECUTABLE:
add_executable(simplelog_example_null)
target_sources(simplelog_example_null PRIVATE
    main.example_null.cpp
)
target_link_libraries(simplelog_example_null
    PRIVATE  cxx_simplelog::simplelog_null
)
target_include_directories(simplelog_example_null
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_options(simplelog_example_null
    PRIVATE  -Wpedantic
)
target_compile_definitions(simplelog_example_null
    PRIVATE
        # NOT-NEEDED: SIMPLELOG_USE_BACKEND_NULL=1
        SIMPLELOG_DIAG=1
)

add_executable(simplelog_example_syslog)
target_sources(simplelog_example_syslog PRIVATE
    main.example_syslog.cpp
)
target_link_libraries(simplelog_example_syslog
    PRIVATE
        cxx_simplelog::simplelog_syslog
        # INHERITED: fmt::fmt
)
target_include_directories(simplelog_example_syslog
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_options(simplelog_example_syslog
    PRIVATE  -Wall -Wpedantic
)
target_compile_definitions(simplelog_example_syslog
    PRIVATE
        SIMPLELOG_DIAG=1
        # INHERITED: SIMPLELOG_USE_BACKEND_SYSLOG=1
)

# ---------------------------------------------------------------------------
# SECTION: Run examples as tests
# ---------------------------------------------------------------------------
set(CXX_FMTLIB "fmt::fmt")    # Use embedded FMT library.
if(NOT TARGET fmt::fmt)
    set(CXX_FMTLIB "spdlog::spdlog")    # Use embedded FMT library.
endif()

# -- EXECUTABLE:
add_executable(example_variadic_args)
target_sources(example_variadic_args PRIVATE
    main.variadic_args_recipe_for_zero_args.cpp
)
target_link_libraries(example_variadic_args PRIVATE
    ${CXX_FMTLIB}
)
list(APPEND EXAMPLE_PROGRAMS  example_variadic_args)

# ---------------------------------------------------------------------------
# SECTION: AUTO-RUN PROGRAMS
# ---------------------------------------------------------------------------
set(EXAMPLE_PROGRAMS
    simplelog_example_spdlog
    simplelog_example_null
    example_variadic_args
)
list(APPEND EXAMPLE_PROGRAMS simplelog_example_syslog)

add_custom_target(examples
    DEPENDS ${EXAMPLE_PROGRAMS}
    COMMAND simplelog_example_spdlog
    COMMAND simplelog_example_null
    COMMENT "RUN: examples"
)

foreach(_EXAMPLE_PROGRAM ${EXAMPLE_PROGRAMS})
    add_custom_target("run.${_EXAMPLE_PROGRAM}"
        COMMAND ${_EXAMPLE_PROGRAM}
        DEPENDS ${_EXAMPLE_PROGRAM}
        COMMENT "RUN: ${_EXAMPLE_PROGRAM}")
endforeach()

# ---------------------------------------------------------------------------
# SECTION: Run examples as tests
# ---------------------------------------------------------------------------
set(SIMPLELOG_AUTO_RUN_EXAMPLES OFF)
enable_testing()

# -- SOLUTION 1: Builds other programs, libs first. Then auto-runs tests.
set(test_examples_TARGET_MODE_ALL "")
if(SIMPLELOG_AUTO_RUN_EXAMPLES)
    set(test_examples_TARGET_MODE_ALL "ALL")
endif()
add_custom_target(test_examples ${test_examples_TARGET_MODE_ALL}
    COMMAND ctest
    DEPENDS ${EXAMPLE_PROGRAMS}
    COMMENT "AUTO-RUN EXAMPLES with: all"
)

# -- TESTS:
add_test(NAME example_simplelog.spdlog   COMMAND simplelog_example_spdlog)
set_tests_properties(example_simplelog.spdlog PROPERTIES
    PASS_REGULAR_EXPRESSION ".*foo.bar::info.*  Hello Alice and Bob")

add_test(NAME example_simplelog.null   COMMAND simplelog_example_null)
set_tests_properties(example_simplelog.null PROPERTIES
    PASS_REGULAR_EXPRESSION "NULL-EXAMPLE: Finished.")

