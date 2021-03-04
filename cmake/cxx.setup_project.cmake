# ===========================================================================
# CMAKE SETUP C++ PROJECT: cmake/cxx.setup_project.cmake
# ===========================================================================
# STATE:  beta
# DESCRIPTION:
#   Provides basic setup for C++ project (common parts)
#   before any targets (like: add_executable(), add_library(), ...)
#   are defined.
#
#   * Setup CMAKE_BUILD_TYPE if undefined
#   * Setup default C/C++ compile-definions based on CMAKE_BUILD_TYPE
#   * Setup CMAKE_CXX_STANDARD, ... undefined
#   * Setup directory-layout (bin/, lib/ directories) in CMAKE_BUILD_DIRECTORY
#
# REQUIRES: INCLUDE BEFORE ANY-TARGET (add_executable(), add_library(), ...)
# DEPENDS ON:
#   * cxx.setup_cxx_standard.cmake
#   * build_config
# ===========================================================================
# SEE: https://cmake.org/cmake/help/v3.18/variable/CMAKE_DEFAULT_BUILD_TYPE.html

include_guard(DIRECTORY)

# -- CMAKE_DEFAULT_BUILD_TYPE:
# MAY CAUSE: CMake Error if CMAKE_GENERATOR does not support it (Ninja, Visual Studio 16 2019, ...)
if(NOT MSVC)
    if(NOT DEFINED CMAKE_DEFAULT_BUILD_TYPE)
        if(DEFINED CMAKE_CONFIGURATION_TYPES)
            list(GET CMAKE_CONFIGURATION_TYPES 0 _CMAKE_DEFAULT_BUILD_TYPE)
            set(CMAKE_DEFAULT_BUILD_TYPE ${_CMAKE_DEFAULT_BUILD_TYPE})
            message(
                STATUS
                    "USE: CMAKE_DEFAULT_BUILD_TYPE=${_CMAKE_DEFAULT_BUILD_TYPE} (from CMAKE_CONFIGURATION_TYPES=${CMAKE_CONFIGURATION_TYPES})"
            )
        else()
            set(_CMAKE_DEFAULT_BUILD_TYPE "Release")
        endif()
    else()
        set(_CMAKE_DEFAULT_BUILD_TYPE ${CMAKE_DEFAULT_BUILD_TYPE})
    endif()
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        "${_CMAKE_DEFAULT_BUILD_TYPE}"
        CACHE STRING "CMake build type: Debug, Release, ..."
    )
endif()

if(NOT DEFINED CTEST_CONFIGURATION_TYPE)
    # -- SUPPORT: MULTI-CONFIGURATION GENERATORS
    set(CTEST_CONFIGURATION_TYPE ${CMAKE_BUILD_TYPE})
endif()
message(
    STATUS
        "USING: CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} (CTEST_CONFIGURATION_TYPE=${CTEST_CONFIGURATION_TYPE})"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG=1)
else()
    add_compile_definitions(NDEBUG=1)
endif()

# -- ARTIFACT DIRECTORY LAYOUT in BINARY_DIR:
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")

# ----------------------------------------------------------------------------
# MORE C++ SETUPS:
# ----------------------------------------------------------------------------
include(WarningsAsErrors)
include(cxx.setup_cxx_standard)
include(build_config)
