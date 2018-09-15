# ===========================================================================
# CMAKE: simplelog Explorations
# ===========================================================================

cmake_minimum_required(VERSION 3.4.0)
project(simplelog VERSION 0.1.0 LANGUAGES CXX)
# OR: enable_language(CXX)

# ---------------------------------------------------------------------------
# SECTION: C++ Compiler Configuration
# ---------------------------------------------------------------------------
# -- CMAKE_CXX_STANDARD: Needs to defined before any target to have effect.
set(CMAKE_CXX_STANDARD 14)  # Enable C++14 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")


# XXX include("${PROJECT_SOURCE_DIR}/../cmake/build_config.cmake")
include("cmake/build_config.cmake")
message(STATUS "USING BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# ---------------------------------------------------------------------------
# SECTION: Target
# ---------------------------------------------------------------------------
add_executable(simplelog_example 
    example_main.cpp)
target_link_libraries(simplelog_example INTERFACE spdlog::spdlog)
target_include_directories(simplelog_example
    PUBLIC
        /usr/local/include
    #     $<INSTALL_INTERFACE:include>
    #     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    # PRIVATE
    #     ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# XXX set_property(TARGET simplelog_example PROPERTY EchoString "CXX-BUILD: hello_app ...")

# ---------------------------------------------------------------------------
# SECTION: AUTO-RUN PROGRAMS
# ---------------------------------------------------------------------------
add_custom_target(run-simplelog_example ALL
    COMMAND simplelog_example
    DEPENDS simplelog_example
    COMMENT "RUN: simplelog_example")

# ---------------------------------------------------------------------------
# SECTION: Unittests
# ---------------------------------------------------------------------------
enable_testing()
set(TEST_PROGRAMS simplelog_example)

# -- SOLUTION 1: Builds other programs, libs first. Then auto-runs tests.
set(RUN_AUTO_TESTS ON)
if(RUN_AUTO_TESTS)
    add_custom_target(tests ALL
        COMMAND ctest
        DEPENDS ${TEST_PROGRAMS}
        COMMENT "AUTO-RUN TESTS with: all")
endif()

# -- TEST PROGRAM: test_hello_Responder
# add_executable(test_hello_Responder
#     test/hello/test_Responder.cpp)
# target_link_libraries(test_hello_Responder HELLO::hello)
# NOT-NEEDED: Due to using the package-dependency: HELLO::hello
#   target_include_directories(test_hello_Responder
#       PRIVATE ${HELLO_LIB_INCLUDE_DIR})

# -- TESTS:
add_test(NAME test_simplelog_example   COMMAND simplelog_example)
set_tests_properties(test_simplelog_example PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\[foo.bar\\] \\[info\\] Hello Alice and Bob")


