# ===========================================================================
# CMAKE: cxx.simplelog
# ===========================================================================

cmake_minimum_required(VERSION 3.14...3.20)

set(MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT ON)
    message(STATUS "cmake.version: ${CMAKE_VERSION} (in MASTER_PROJECT)")
endif()

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
if(MASTER_PROJECT)
    include(ccache)
    # MAYBE:
    # include(GenerateExportHeader)
    # include(WriteCompilerDetectionHeader)
endif()

# ---------------------------------------------------------------------------
# PROJECT: simplelog
# ---------------------------------------------------------------------------
project(
    cxx.simplelog
    VERSION 0.2.0
    LANGUAGES CXX
)

option(BUILD_EXAMPLES "Enable simplelog examples" ${MASTER_PROJECT})
option(BUILD_TESTING "Enable tests (and examples)" ${MASTER_PROJECT})
option(SIMPLELOG_BUILD_EXAMPLES "Enable simplelog examples" ${MASTER_PROJECT})
option(SIMPLELOG_BUILD_TESTS "Enable tests (and examples)" ${MASTER_PROJECT})

option(SIMPLELOG_USE_BACKEND_SPDLOG "Use spdlog as simplelog-backend" ON)
option(SIMPLELOG_USE_BACKEND_SYSLOG "Use syslog as simplelog-backend" ON)

option(DOCTEST_NO_INSTALL "Normally exclude doctest from packages" YES)
option(SPDLOG_INSTALL "need to install" YES)
option(FMT_INSTALL "need to install" YES)

include(cxx.setup_project)

# ---------------------------------------------------------------------------
# SECTION: Find Packages
# ---------------------------------------------------------------------------
set(SPDLOG_MIN_VERSION 1.8.2)
set(FMT_MIN_VERSION 7.1.3)


# ---- Add dependencies via CPM ----
# see https://github.com/cpm-cmake/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
    NAME PackageProject.cmake
    GITHUB_REPOSITORY TheLartians/PackageProject.cmake
    VERSION 1.5.1
)

CPMAddPackage(
    NAME fmt
    GIT_TAG ${FMT_MIN_VERSION}
    GITHUB_REPOSITORY fmtlib/fmt # to get an installable target
    OPTIONS "FMT_INSTALL YES"
)

CPMAddPackage(
    NAME spdlog
    GIT_TAG v${SPDLOG_MIN_VERSION}
    GITHUB_REPOSITORY gabime/spdlog # to use our installed fmt lib
    OPTIONS "SPDLOG_FMT_EXTERNAL YES"
)

if(SIMPLELOG_USE_BACKEND_SYSLOG)
    find_package(Syslog)
    if(NOT Syslog_FOUND)
        message(WARNING "Syslog_FOUND=${Syslog_FOUND}")
        set(SIMPLELOG_USE_BACKEND_SYSLOG OFF)
    endif()
endif()

# ---------------------------------------------------------------------------
# SECTION: LIBS
# ---------------------------------------------------------------------------
set(PROJECT_NAMESPACE cxx_simplelog)
set(SIMPLELOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# -- HEADER-ONLY LIBS:
# LIBRARY: cxx_simplelog::simplelog         -- To reference generic library.
# LIBRARY: cxx_simplelog::simplelog_null    -- Use simplelog w/ backend=null
# LIBRARY: cxx_simplelog::simplelog_spdlog  -- Use simplelog w/ backend=spdlog
add_subdirectory(src/simplelog)
add_subdirectory(src/simplelog/backend)
# add_subdirectory(src/simplelog/backend/null   simplelog_backend_null)
# add_subdirectory(src/simplelog/backend/spdlog simplelog_backend_spdlog)

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

    CPMAddPackage(
        NAME doctest
        GITHUB_REPOSITORY onqtam/doctest
        GIT_TAG 2.4.5
    )
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------------------
# SECTION: Install
# ----------------------------------------------------------------------------
# done at subdirs! CK
# ----------------------------------------------------------------------------
# SECTION: Pack
# ----------------------------------------------------------------------------
# HINT: Source-pack includes CMAKE_CURRENT_BUILDIR, ...
# set(CPACK_SOURCE_GENERATOR "ZIP")
# set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
# set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
# set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
# set(CPACK_SOURCE_IGNORE_FILES "build/;build.*/;.attic/;.git/;.vscode/;.idea/;\.DS_Store;__.*/")
# # set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
#
# include(CPack)
