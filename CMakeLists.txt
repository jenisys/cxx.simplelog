# ===========================================================================
# CMAKE: cxx.simplelog
# ===========================================================================

cmake_minimum_required(VERSION 3.15)

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
    # DEPRECATED: include(WriteCompilerDetectionHeader)
endif()

# ---------------------------------------------------------------------------
# PROJECT: simplelog
# ---------------------------------------------------------------------------
project(cxx.simplelog VERSION 0.1.11 LANGUAGES CXX)

option(BUILD_EXAMPLES "Enable simplelog examples" OFF)
option(BUILD_TESTING  "Enable tests (and examples)" OFF)

option(SIMPLELOG_USE_BACKEND_SPDLOG "Use spdlog as simplelog-backend" ON)
option(SIMPLELOG_USE_BACKEND_SYSLOG "Use syslog as simplelog-backend" ON)
option(SIMPLELOG_USE_BUNDLED_SPDLOG "Use bundled spdlog library" ON)
option(SIMPLELOG_USE_BUNDLED_FMTLIB "Use bundled fmt library" ON)
option(SIMPLELOG_CPACK_SOURCE_IGNORE_THIRD_PARTY "Bundle third-party libs with source-package" ON)
option(SIMPLELOG_BUILD_EXAMPLES "Enable simplelog examples"   ${MASTER_PROJECT})
option(SIMPLELOG_BUILD_TESTS    "Enable tests (and examples)" ${MASTER_PROJECT})
set(DOCTEST_NO_INSTALL ON CACHE BOOL "Normally exclude doctest from packages" FORCE)
set(SPDLOG_INSTALL  ${SIMPLELOG_USE_BUNDLED_SPDLOG} CACHE BOOL
                    "Normally include spdlog from packages" FORCE)
set(FMT_INSTALL ${SIMPLELOG_USE_BUNDLED_FMTLIB} CACHE BOOL
                "Normally include fmt from packages" FORCE)

include(cxx.setup_project)
# DISABLED: include(cxx.use_sanitizer)
# -- WIP: Coverage
# PROBLEMS:
#   * Directory seems to be offset by one.
#   * BASE_DIRECTORY
#   * EXCLUDE: Does not filter-out things
if(CODE_COVERAGE)
    message(STATUS "Coverage: Setup coverage target for LCOV")
    setup_target_for_coverage_lcov(NAME coverage
        EXECUTABLE ${CMAKE_CTEST_COMMAND}
        # BASE_DIRECTORY "./"
        # BASE_DIRECTORY "../"
        # BASE_DIRECTORY "../cxx.simplelog"
        EXCLUDE
            "tests/*"
            "lib/*"
            "${CMAKE_BINARY_DIR}/tests/*"
            "${CMAKE_BINARY_DIR}/lib/*"
            # "${CMAKE_CURRENT_SOURCE_DIR}/tests/*"
            # "${CMAKE_CURRENT_SOURCE_DIR}/lib/*"
    )
endif()

# ---------------------------------------------------------------------------
# SECTION: BOOTSTRAP -- When wstool update was not done yet
# ---------------------------------------------------------------------------
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake_project/bootstrap_subprojects_with_wstool.cmake")


# ---------------------------------------------------------------------------
# SECTION: Find Packages
# ---------------------------------------------------------------------------
# SHORTCUT: Supports spdlog-1.5.0, spdlog-1.4.2 at least
# CURRENT: SPDLOG_VERSION = 1.8.0
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
    # find_package(doctest REQUIRED)
    add_subdirectory(lib/doctest doctest)
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
