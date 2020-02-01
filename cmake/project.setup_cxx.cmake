# ===========================================================================
# CMAKE PART: PROJECT-SPECIFIC: Setup C++ Build Projects
# ===========================================================================
# STATE: alpha (may become deprecated, superceeded by: cxx.setup_project.cmake)
# ===========================================================================
# USE: INCLUDE-BEFORE add_executable(), add_library()

include_guard(DIRECTORY)

# ----------------------------------------------------------------------------
# CMAKE SETUP:
# ----------------------------------------------------------------------------
# XXX-NOT-WORKING: file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/.." TOPDIR)
# XXX get_filename_component(TOPDIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE )
# set(TOPDIR "${CMAKE_CURRENT_LIST_DIR}/..")
get_filename_component(TOPDIR "${CMAKE_CURRENT_LIST_DIR}" DIRECTORY CACHE)
message(STATUS "USING: TOPDIR=${TOPDIR}")

# -- SETUP: CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

# ----------------------------------------------------------------------------
# CMAKE C++ COMPILER SETUP:
# ----------------------------------------------------------------------------
include("${CMAKE_CURRENT_LIST_DIR}/cxx.setup_cxx_standard.cmake")


# ----------------------------------------------------------------------------
# MORE GENERIC PARTS:
# ----------------------------------------------------------------------------
# DISABLED: include("${CMAKE_CURRENT_LIST_DIR}/project.build_config.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/build_config.cmake")


# ----------------------------------------------------------------------------
# CMAKE PROJECT-SPECIFIC SETUP:
# ----------------------------------------------------------------------------
set(_BUILD_CONFIG "${CMAKE_SYSTEM_PROCESSOR}_${CMAKE_BUILD_TYPE}")

# -- NEEDED-FOR:
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_compile_definitions(NDEBUG=1)
else()
    add_compile_definitions(DEBUG=1)
endif()

# -- DEFAULT INCLUDE-DIRS:
# include_directories("${TOPDIR}")
# -- DEFAULT LINK-DIRS:
# link_directories()
include(CMakePackageConfigHelpers)
