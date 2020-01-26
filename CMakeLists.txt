# ===========================================================================
# CMAKE: cxx.simplelog
# ===========================================================================

cmake_minimum_required(VERSION 3.12)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ccache)

# MAYBE:
include(GenerateExportHeader)
include(WriteCompilerDetectionHeader)

# ---------------------------------------------------------------------------
# PROJECT: simplelog
# ---------------------------------------------------------------------------
project(cxx.simplelog VERSION 0.1.8 LANGUAGES CXX)

option(SIMPLELOG_USE_BACKEND_SPDLOG "Use spdlog as simplelog-backend" ON)
option(SIMPLELOG_USE_BUNDLED_SPDLOG "Use bundled spdlog library" ON)
option(SIMPLELOG_USE_BUNDLED_FMTLIB "Use bundled fmt library" ON)
option(SIMPLELOG_CPACK_SOURCE_IGNORE_THIRD_PARTY "Bundle third-party libs with source-package" ON)
option(BUILD_EXAMPLES "Enable simplelog examples" ON)
option(BUILD_TESTING "Enable tests (and examples)" ON)
set(DOCTEST_NO_INSTALL ON CACHE BOOL "Normally exclude doctest from packages" FORCE)
set(SPDLOG_INSTALL  ${SIMPLELOG_USE_BUNDLED_SPDLOG} CACHE BOOL
                    "Normally include spdlog from packages" FORCE)

include(cxx.setup_project)
# # -- CMAKE_CONFIGURATION_TYPES
# if(NOT DEFINED CMAKE_BUILD_TYPE)
#     SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "CMake build type: Debug, Release, ...")
# endif()
# # SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
# # IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
# #    SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
# # ENDIF()
# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_compile_definitions(DEBUG=1)
# endif()

# # -- ARTIFACT DIRECTORY LAYOUT in BINARY_DIR:
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")

# ---------------------------------------------------------------------------
# SECTION: C++ Compiler Configuration
# ---------------------------------------------------------------------------
# -- CMAKE_CXX_STANDARD: Needs to defined before any target to have effect.
# set(CMAKE_CXX_STANDARD 14)  # Enable C++14 standard
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")
# include("cmake/cxx.setup_cxx_standard.cmake")
# include("cmake/build_config.cmake")

# ---------------------------------------------------------------------------
# SECTION: Find Packages
# ---------------------------------------------------------------------------
# SHORTCUT:
set(SPDLOG_MIN_VERSION "1.4.2")
# find_package(spdlog ${SPDLOG_MIN_VERSION} REQUIRED)
# DISABLED: if(NOT spdlog_FOUND)
if(TRUE)
    set(SIMPLELOG_USE_BUNDLED_SPDLOG ON)
    # set(spdlog_FOUND ON)
endif()

# -- THIRD-PARTY PARTS:
# set(SIMPLELOG_USE_BUNDLED_SPDLOG ON)
if(SIMPLELOG_USE_BUNDLED_SPDLOG)
    message(STATUS "USING: spdlog (bundled, as subproject)")
    set(SPDLOG_INSTALL ON)
    add_subdirectory(lib/spdlog spdlog)
endif()
if(SIMPLELOG_USE_BUNDLED_FMTLIB)
    message(STATUS "USING: fmt (bundled, as subproject)")
    add_subdirectory(lib/fmt fmt)
endif()
# TODO: SPDLOG_VERSION, FMT_VERSION is EMPTY or UNDEFINED
message(STATUS "USING: spdlog.version=${SPDLOG_VERSION} (expected: ${SPDLOG_MIN_VERSION}, bundled: ${SIMPLELOG_USE_BUNDLED_SPDLOG})")
message(STATUS "USING: fmt.version=${FMT_VERSION} (bundled: ${SIMPLELOG_USE_BUNDLED_FMTLIB})")

# ---------------------------------------------------------------------------
# SECTION: LIBS
# ---------------------------------------------------------------------------
set(PROJECT_NAMESPACE "cxx_simplelog")
set(SIMPLELOG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SIMPLELOG_LIBRARIES
    simplelog
    simplelog_null
    simplelog_spdlog
)

# -- HEADER-ONLY LIBS:
# LIBRARY: cxx_simplelog::simplelog         -- To reference generic library.
# LIBRARY: cxx_simplelog::simplelog_null    -- Use simplelog w/ backend=null
# LIBRARY: cxx_simplelog::simplelog_spdlog  -- Use simplelog w/ backend=spdlog
add_subdirectory(src/simplelog simplelog)
add_subdirectory(src/simplelog/backend/null   simplelog_backend_null)
add_subdirectory(src/simplelog/backend/spdlog simplelog_backend_spdlog)

# ---------------------------------------------------------------------------
# SECTION: EXECUTABLES
# ---------------------------------------------------------------------------
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ---------------------------------------------------------------------------
# SECTION: Unittests / Examples
# ---------------------------------------------------------------------------
if(BUILD_TESTING)
    include(CTest)
    # find_package(doctest REQUIRED)
    add_subdirectory(lib/doctest doctest)
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------------------
# SECTION: Install
# ----------------------------------------------------------------------------
# MORE: https://foonathan.net/2016/03/cmake-install/
install(TARGETS ${SIMPLELOG_LIBRARIES}
    EXPORT ${PROJECT_NAMESPACE}-targets DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT ${PROJECT_NAMESPACE}-targets
        NAMESPACE   ${PROJECT_NAMESPACE}::
        DESTINATION lib/cmake/${PROJECT_NAMESPACE})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/simplelog
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
        PATTERN ".cmake" EXCLUDE
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/.cmake/project-config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAMESPACE}-config.cmake"
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAMESPACE}"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAMESPACE}-config.cmake"
        DESTINATION "lib/cmake/${PROJECT_NAMESPACE}")

# -- MAYBE:
# export(EXPORT cpp_compat NAMESPACE CppCompat)
# ----------------------------------------------------------------------------
# SECTION: Pack
# ----------------------------------------------------------------------------
# HINT: Source-pack includes CMAKE_CURRENT_BUILDIR, ...
# set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES "build/;build.*/;.attic/;.git/;.vscode/;__;\.DS_Store")
if(SIMPLELOG_CPACK_SOURCE_IGNORE_THIRD_PARTY)
    message("CPACK-SOURCE: Ignore bundled third-party libraries.")
    set(CPACK_SOURCE_IGNORE_FILES "${CPACK_SOURCE_IGNORE_FILES};lib/")
endif()
# set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

include(CPack)
