# ===========================================================================
# CMAKE: simplelog Explorations
# ===========================================================================

cmake_minimum_required(VERSION 3.12.0)
project(boostlog.example VERSION 0.1.0 LANGUAGES CXX)


# ---------------------------------------------------------------------------
# SECTION: C++ Compiler Configuration
# ---------------------------------------------------------------------------
# -- CMAKE_CXX_STANDARD: Needs to defined before any target to have effect.
set(CMAKE_CXX_STANDARD 14)  # Enable C++14 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")


include("${PROJECT_SOURCE_DIR}/../cmake/build_config.cmake")
message(STATUS "USING BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# ---------------------------------------------------------------------------
# SECTION: Find Packages
# ---------------------------------------------------------------------------
set(BOOSTLOG_COMPONENTS  "log" "log_setup" "date_time" "system" "filesystem")
set(BOOSTLOG_COMPILE_DEFINITIONS    BOOST_LOG_DYN_LINK=1)
set(BOOSTLOG_LIBRARIES 
    Boost::log Boost::log_setup 
    Boost::date_time 
    Boost::system 
    Boost::filesystem
)
find_package(Boost COMPONENTS ${BOOSTLOG_COMPONENTS})

# set(BOOST_INCDIR "/usr/local/include")
# ---------------------------------------------------------------------------
# SECTION: Target
# ---------------------------------------------------------------------------
add_executable(boostlog_example  basic_usage.main.cpp)
target_link_libraries(boostlog_example 
    PRIVATE ${BOOSTLOG_LIBRARIES}
    # PRIVATE Boost::log Boost::log_setup Boost::date_time Boost::system Boost::filesystem
)
target_include_directories(boostlog_example
    PRIVATE ${Boost_INCLUDE_DIRS}
)
target_compile_definitions(boostlog_example
    PRIVATE ${BOOSTLOG_COMPILE_DEFINITIONS}
)
add_custom_target(run.boostlog_example ALL
    COMMAND boostlog_example
    DEPENDS boostlog_example
    COMMENT "RUN: boostlog_example")


