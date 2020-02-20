# ===========================================================================
# CMAKE: cxx.simplelog
# ===========================================================================

cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ccache)

# MAYBE:
# include(GenerateExportHeader)
# include(WriteCompilerDetectionHeader)

# ---------------------------------------------------------------------------
# PROJECT: simplelog
# ---------------------------------------------------------------------------
project(cxx.simplelog VERSION 0.1.8 LANGUAGES CXX)

option(SIMPLELOG_USE_CPACK "Use cpack" OFF)
option(SIMPLELOG_USE_BACKEND_SPDLOG "Use spdlog as simplelog-backend" ON)

# fmt related options, only used if bundled fmt is used!
option(FMT_INSTALL "Generate the install target." ON)

# spdlog related options, only used if bundled spdlog is used!
option(SPDLOG_FMT_EXTERNAL "Use external fmt library instead of bundled" ON)
option(SPDLOG_INSTALL "Generate the install target" ON)

option(BUILD_EXAMPLES "Enable simplelog examples" off)
option(BUILD_TESTING "Enable tests (and examples)" ON)

# doctest related options, only used for intern test!
set(DOCTEST_NO_INSTALL ON CACHE BOOL "Normally exclude doctest from packages" FORCE)

include(cxx.setup_project)

# MAYBE: add check target
include(clang-tidy)

# ---------------------------------------------------------------------------
# SECTION: Find Packages
# ---------------------------------------------------------------------------
include(FetchContent)
if(CMAKE_VERSION VERSION_LESS "3.14")
    function(fetchcontent_makeavailable name)
        fetchcontent_getproperties(${name})
        if(NOT ${name}_POPULATED)
            fetchcontent_populate(${name})
            add_subdirectory(${${name}_SOURCE_DIR} ${${name}_BINARY_DIR})
            include_directories(${${name}_SOURCE_DIR}/include)
        endif()
    endfunction()
endif()

if(SPDLOG_FMT_EXTERNAL)
    set(FMT_MIN_VERSION 6.1.2)
    find_package(fmt ${FMT_MIN_VERSION} REQUIRED)
    if(NOT TARGET fmt::fmt)
        message(WARNING "Try to get fmt with FetchContent ...")
        fetchcontent_declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG ${FMT_MIN_VERSION}
        )
        fetchcontent_makeavailable(fmt)
    endif()
endif()

set(SPDLOG_MIN_VERSION 1.5.0)
find_package(spdlog ${SPDLOG_MIN_VERSION} REQUIRED)
if(NOT TARGET spdlog::spdlog)
    message(WARNING "Try to get spdlog with FetchContent ...")
    fetchcontent_declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v${SPDLOG_MIN_VERSION}
    )
    fetchcontent_makeavailable(spdlog)
endif()

if(BUILD_TESTING)
    set(DOCTEST_MIN_VERSION 2.3.6)
    find_package(doctest ${DOCTEST_MIN_VERSION} REQUIRED)
    if(NOT TARGET doctest::doctest)
        message(WARNING "Try to get doctest with FetchContent ...")
        fetchcontent_declare(
            doctest
            GIT_REPOSITORY https://github.com/onqtam/doctest.git
            GIT_TAG ${DOCTEST_MIN_VERSION}
        )
        fetchcontent_makeavailable(doctest)
    endif()
endif()

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
    enable_testing()
    add_subdirectory(tests)

    # test coverage option => custom target will be lcov
    if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
        include(CodeCoverage)

        set(COVERAGE_EXCLUDES
            '/tmp/*' '/usr/*' '/opt/*'
            '${CMAKE_BINARY_DIR}/_deps/*'
            '${CMAKE_SOURCE_DIR}/lib/*'
            '/Applications/Xcode.app/*'
        )
        setup_target_for_coverage(
            NAME lcov   # custom target.
            EXECUTABLE ctest    # the test driver executable that runs the tests.
        )
    endif()
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

if(SIMPLELOG_USE_CPACK)
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
    set(CPACK_SOURCE_IGNORE_FILES "build/;.build-*;build.*/;.attic/;.git/;.vscode/;__;\.DS_Store")
    # set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

    include(CPack)
endif()
