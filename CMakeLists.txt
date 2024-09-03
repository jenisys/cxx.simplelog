# ===========================================================================
# CMAKE: cxx.simplelog
# ===========================================================================

cmake_minimum_required(VERSION 3.15..3.30)

set(MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT ON)
    message(STATUS "cmake.version: ${CMAKE_VERSION} (in MASTER_PROJECT)")
endif()

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
if(MASTER_PROJECT)
    include(ccache)
    # MAYBE:
    include(GenerateExportHeader)
    # DISABLED: include(WriteCompilerDetectionHeader)
endif()

# ---------------------------------------------------------------------------
# PROJECT: simplelog
# ---------------------------------------------------------------------------
project(cxx.simplelog VERSION 0.3.0 LANGUAGES CXX)

option(BUILD_EXAMPLES "Enable simplelog examples" OFF)
option(BUILD_TESTING  "Enable tests (and examples)" OFF)

option(SIMPLELOG_USE_BACKEND_SPDLOG "Use spdlog as simplelog-backend" ON)
option(SIMPLELOG_USE_BACKEND_SYSLOG "Use syslog as simplelog-backend" ON)
option(SIMPLELOG_CPACK_SOURCE_IGNORE_THIRD_PARTY "Bundle third-party libs with source-package" ON)
option(SIMPLELOG_BUILD_EXAMPLES "Enable simplelog examples"   ${MASTER_PROJECT})
option(SIMPLELOG_BUILD_TESTS    "Enable tests (and examples)" ${MASTER_PROJECT})
set(DOCTEST_NO_INSTALL ON CACHE BOOL "Normally exclude doctest from packages" FORCE)
set(SPDLOG_INSTALL  ${SIMPLELOG_USE_BACKEND_SPDLOG} CACHE BOOL
                    "Normally include spdlog from packages" FORCE)
set(FMT_INSTALL ON CACHE BOOL  "Normally include fmt from packages" FORCE)

include(cxx.setup_project)
include(CPM)


# ---------------------------------------------------------------------------
# SECTION: Find Packages
# ---------------------------------------------------------------------------
# SEE: https://github.com/gabime/spdlog
# SEE: https://github.com/gabime/spdlog/wiki/9.-CMake
CPMAddPackage(NAME spdlog
    VERSION 1.14.1
    GITHUB_REPOSITORY gabime/spdlog
)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")

# -- SEE: https://github.com/doctest/doctest
# https://github.com/doctest/doctest/blob/master/doc/markdown/build-systems.md
if(SIMPLELOG_BUILD_TESTS)
    CPMAddPackage(NAME doctest
        VERSION 2.4.11
        GITHUB_REPOSITORY doctest/doctest
    )
endif()

# find_package(Syslog)
# message(STATUS "Syslog_FOUND=${Syslog_FOUND}")
# if(NOT Syslog_FOUND)
#     set(SIMPLELOG_USE_BACKEND_SYSLOG OFF)
# endif()

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
add_subdirectory(src/simplelog/backend)
# add_subdirectory(src/simplelog/backend/null   simplelog_backend_null)
# add_subdirectory(src/simplelog/backend/spdlog simplelog_backend_spdlog)
if(SIMPLELOG_USE_BACKEND_SYSLOG)
    # add_subdirectory(src/simplelog/backend/syslog simplelog_backend_syslog)
    list(APPEND SIMPLELOG_LIBRARIES simplelog_syslog)
endif()

# ---------------------------------------------------------------------------
# SECTION: EXECUTABLES
# ---------------------------------------------------------------------------
if(SIMPLELOG_BUILD_EXAMPLES OR BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ---------------------------------------------------------------------------
# SECTION: Unittests / Examples
# ---------------------------------------------------------------------------
if(SIMPLELOG_BUILD_TESTS OR BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------------------
# SECTION: Install
# ----------------------------------------------------------------------------
# MORE: https://foonathan.net/2016/03/cmake-install/
install(TARGETS ${SIMPLELOG_LIBRARIES}
    EXPORT ${PROJECT_NAMESPACE}-targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR})
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
set(CPACK_SOURCE_IGNORE_FILES "build/;build.*/;.attic/;.git/;.vscode/;.idea/;\.DS_Store;__.*/")
if(SIMPLELOG_CPACK_SOURCE_IGNORE_THIRD_PARTY)
    message("CPACK-SOURCE: Ignore bundled third-party libraries.")
    set(CPACK_SOURCE_IGNORE_FILES "${CPACK_SOURCE_IGNORE_FILES};lib/")
endif()
# set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

include(CPack)
