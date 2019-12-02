# ===========================================================================
# CMAKE: cxx.simplelog/examples
# ===========================================================================


# ---------------------------------------------------------------------------
# SECTION: EXECUTABLES
# ---------------------------------------------------------------------------
add_executable(simplelog_example_spdlog
    main.example_spdlog.cpp
)
target_link_libraries(simplelog_example_spdlog 
    PRIVATE
        cxx_simplelog::simplelog
        spdlog::spdlog
        # PREPARED: fmt::fmt
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
add_executable(simplelog_example_null
    main.example_null.cpp
)
target_link_libraries(simplelog_example_null 
    PRIVATE  cxx_simplelog::simplelog
)
target_compile_options(simplelog_example_null
    PRIVATE  -Wpedantic
)
target_compile_definitions(simplelog_example_null
    PRIVATE  
        SIMPLELOG_USE_BACKEND_NULL=1
        SIMPLELOG_DIAG=1
)
# ---------------------------------------------------------------------------
# SECTION: AUTO-RUN PROGRAMS
# ---------------------------------------------------------------------------
set(EXAMPLE_PROGRAMS
    simplelog_example_spdlog
    simplelog_example_null
)

add_custom_target(examples
    DEPENDS ${EXAMPLE_PROGRAMS}
    COMMAND simplelog_example_spdlog
    COMMAND simplelog_example_null
    COMMENT "RUN: examples"
)

add_custom_target(run.simplelog_example_spdlog
    COMMAND simplelog_example_spdlog
    DEPENDS simplelog_example_spdlog
    COMMENT "RUN: simplelog_example_spdlog")

add_custom_target(run.simplelog_example_null
    COMMAND simplelog_example_null
    DEPENDS simplelog_example_null
    COMMENT "RUN: simplelog_example_null")

# ---------------------------------------------------------------------------
# SECTION: Run examples as tests
# ---------------------------------------------------------------------------
set(SIMPLELOG_AUTO_RUN_EXAMPLES OFF)
include(CTest)
    
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
