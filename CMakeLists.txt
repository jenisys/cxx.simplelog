# ===========================================================================
# CMAKE: simplelog Explorations
# ===========================================================================

cmake_minimum_required(VERSION 3.4.0)
project(simplelog VERSION 0.1.0 LANGUAGES CXX)
# OR: enable_language(CXX)
option(BOOSTLOG_EXAMPLE_ON "Enable boost.log example" ON)

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
# SECTION: Find Packages
# ---------------------------------------------------------------------------
# SHORTCUT:
# set(SPDLOG_INCDIR "/usr/local/include")
find_package(spdlog 1.1.0 REQUIRED)
message(STATUS "USING: spdlog")

set(BOOSTLOG_COMPONENTS  "log" "log_setup" "date_time" "system" "filesystem")
set(BOOSTLOG_COMPILE_DEFINITIONS    BOOST_LOG_DYN_LINK=1)
set(BOOSTLOG_LIBRARIES 
    Boost::log 
    Boost::log_setup 
    Boost::date_time 
    Boost::system 
    Boost::filesystem
)
find_package(Boost COMPONENTS ${BOOSTLOG_COMPONENTS} REQUIRED)
# NOT-NEEDED: set(BOOST_INCDIR "/usr/local/include")

# ---------------------------------------------------------------------------
# SECTION: Target
# ---------------------------------------------------------------------------
add_executable(simplelog_example_spdlog
    example_spdlog_main.cpp)
target_link_libraries(simplelog_example_spdlog INTERFACE spdlog::spdlog)
target_include_directories(simplelog_example_spdlog
    # PUBLIC ${SPDLOG_INCDIR}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
# set_property(TARGET simplelog_example_spdlog::simplelog_example_spdlog
#    INTERFACE_COMPILE_DEFINITIONS
#        "SIMPLELOG_USE_BACKEND_SPDLOG=1"
# )
# XXX set_property(TARGET simplelog_example PROPERTY EchoString "CXX-BUILD: hello_app ...")

add_executable(simplelog_example_null
    example_null_main.cpp)
target_include_directories(simplelog_example_null
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# DISABLED: Link problems: Missing symbol
if(BOOSTLOG_EXAMPLE_ON)
    add_executable(simplelog_example_boostlog example_boostlog_main.cpp)
    target_link_libraries(simplelog_example_boostlog 
        PRIVATE ${BOOSTLOG_LIBRARIES}
        # PRIVATE Boost::log Boost::log_setup Boost::date_time Boost::system Boost::filesystem
    )
    target_include_directories(simplelog_example_boostlog
        PUBLIC ${Boost_INCLUDE_DIRS}
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    target_compile_definitions(simplelog_example_boostlog
        PRIVATE ${BOOSTLOG_COMPILE_DEFINITIONS}
    )
endif()


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

if(BOOSTLOG_EXAMPLE_ON)
    add_custom_target(run.simplelog_example_boostlog ALL
        COMMAND simplelog_example_boostlog
        DEPENDS simplelog_example_boostlog
        COMMENT "RUN: simplelog_example_boostlog")
endif()

# ---------------------------------------------------------------------------
# SECTION: Unittests
# ---------------------------------------------------------------------------
enable_testing()
set(TEST_PROGRAMS
    simplelog_example_spdlog
    simplelog_example_null
)
if(BOOSTLOG_EXAMPLE_ON)
    list(APPEND TEST_PROGRAMS simplelog_example_boostlog)
endif()


# -- SOLUTION 1: Builds other programs, libs first. Then auto-runs tests.
set(RUN_AUTO_TESTS ON)
if(RUN_AUTO_TESTS)
    add_custom_target(tests ALL
        COMMAND ctest
        DEPENDS ${TEST_PROGRAMS}
        COMMENT "AUTO-RUN TESTS with: all")
endif()

# -- TEST PROGRAM: test.hello_Responder
# add_executable(test.hello_Responder
#     test/hello/test.Responder.cpp)
# target_link_libraries(test.hello_Responder HELLO::hello)
# NOT-NEEDED: Due to using the package-dependency: HELLO::hello
#   target_include_directories(test.hello_Responder
#       PRIVATE ${HELLO_LIB_INCLUDE_DIR})

# -- TESTS:
add_test(NAME test.simplelog_example_spdlog   COMMAND simplelog_example_spdlog)
set_tests_properties(test.simplelog_example_spdlog PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\[foo.bar\\] \\[info\\] Hello Alice and Bob")

add_test(NAME test.simplelog_example_null   COMMAND simplelog_example_null)
set_tests_properties(test.simplelog_example_null PROPERTIES 
    PASS_REGULAR_EXPRESSION "NULL-EXAMPLE: Finished.")

