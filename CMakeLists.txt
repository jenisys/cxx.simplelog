# ===========================================================================
# CMAKE: cxx.simplelog
# ===========================================================================

cmake_minimum_required(VERSION 3.12)
project(simplelog VERSION 0.1.2 LANGUAGES CXX)

option(SIMPLELOG_USE_BACKEND_SPDLOG "Use spdlog as simplelog-backend" ON)
option(SIMPLELOG_USE_BUNDLED_SPDLOG "Use bundled spdlog library" OFF)
option(SIMPLELOG_USE_BUNDLED_FMTLIB "Use bundled spdlog library" OFF)
option(BUILD_TESTING "Enable tests (and examples)" ON)

# ---------------------------------------------------------------------------
# SECTION: C++ Compiler Configuration
# ---------------------------------------------------------------------------
# -- CMAKE_CXX_STANDARD: Needs to defined before any target to have effect.
set(CMAKE_CXX_STANDARD 14)  # Enable C++14 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")


include("cmake/build_config.cmake")
message(STATUS "USING BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# ---------------------------------------------------------------------------
# SECTION: Find Packages
# ---------------------------------------------------------------------------
# SHORTCUT: set(SPDLOG_VERSION "1.4.2")
find_package(spdlog REQUIRED)
if(NOT spdlog_FOUND)
    set(SIMPLELOG_USE_BUNDLED_SPDLOG ON)
endif()

# -- THIRD-PARTY PARTS:
if(SIMPLELOG_USE_BUNDLED_SPDLOG)
    message(STATUS "USING: spdlog (bundled, as subproject)")
    add_subdirectory(lib/spdlog spdlog)
endif()
if(SIMPLELOG_USE_BUNDLED_FMTLIB)
    message(STATUS "USING: fmt (bundled, as subproject)")
    add_subdirectory(lib/fmt fmt)
endif()

# ---------------------------------------------------------------------------
# SECTION: LIBS
# ---------------------------------------------------------------------------
# -- HEADER-ONLY LIBRARY:
add_library(simplelog INTERFACE)
add_library(SimpleLog::simplelog ALIAS simplelog)
target_include_directories(simplelog
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)
# -- SIMPLELOG DEFAULT-BACKEND:
if(SIMPLELOG_USE_BACKEND_SPDLOG)
    target_link_libraries(simplelog INTERFACE spdlog::spdlog)
    set_target_properties(simplelog 
        PROPERTIES INTERFACE_COMPILE_DEFINITIONS
            "SIMPLELOG_USE_BACKEND_SPDLOG=1"
    )
endif()


# ---------------------------------------------------------------------------
# SECTION: EXECUTABLES
# ---------------------------------------------------------------------------
add_executable(simplelog_example_spdlog
    main.example_spdlog.cpp
)
target_link_libraries(simplelog_example_spdlog 
    PRIVATE
        SimpleLog::simplelog
        spdlog::spdlog
        # PREPARED: fmt::fmt
)
target_compile_options(simplelog_example_spdlog
    PRIVATE  -Wall -Wpedantic
)
target_compile_definitions(simplelog_example_spdlog
    PRIVATE  SIMPLELOG_USE_BACKEND_SPDLOG=1
)

# -- EXECUTABLE:
add_executable(simplelog_example_null
    main.example_null.cpp
)
target_link_libraries(simplelog_example_null 
    PRIVATE  SimpleLog::simplelog
)
target_compile_options(simplelog_example_null
    PRIVATE  -Wpedantic
)
target_compile_definitions(simplelog_example_null
    PRIVATE  SIMPLELOG_USE_BACKEND_NULL=1
)
# ---------------------------------------------------------------------------
# SECTION: AUTO-RUN PROGRAMS
# ---------------------------------------------------------------------------
add_custom_target(run.simplelog_example_spdlog ALL
    COMMAND simplelog_example_spdlog
    DEPENDS simplelog_example_spdlog
    COMMENT "RUN: simplelog_example_spdlog")

add_custom_target(run.simplelog_example_null ALL
    COMMAND simplelog_example_null
    DEPENDS simplelog_example_null
    COMMENT "RUN: simplelog_example_null")

# ---------------------------------------------------------------------------
# SECTION: Unittests / Examples
# ---------------------------------------------------------------------------
if(BUILD_TESTING)
    enable_testing()
    set(TEST_PROGRAMS
        simplelog_example_spdlog
        simplelog_example_null
    )


    # -- SOLUTION 1: Builds other programs, libs first. Then auto-runs tests.
    set(RUN_AUTO_TESTS ON)
    if(RUN_AUTO_TESTS)
        add_custom_target(tests ALL
            COMMAND ctest
            DEPENDS ${TEST_PROGRAMS}
            COMMENT "AUTO-RUN TESTS with: all")
    endif()

    # -- TESTS:
    add_test(NAME test.simplelog_example_spdlog   COMMAND simplelog_example_spdlog)
    set_tests_properties(test.simplelog_example_spdlog PROPERTIES 
        PASS_REGULAR_EXPRESSION "\\[foo.bar\\] \\[info\\] Hello Alice and Bob")

    add_test(NAME test.simplelog_example_null   COMMAND simplelog_example_null)
    set_tests_properties(test.simplelog_example_null PROPERTIES 
        PASS_REGULAR_EXPRESSION "NULL-EXAMPLE: Finished.")

endif()
