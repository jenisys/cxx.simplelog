# ===========================================================================
# FIND: doctest
# ===========================================================================
# NOTE: Bundled w/ project

# TOPDIR := "${CMAKE_CURRENT_LIST_DIR}/.."
# set(doctest_ROOT "${CMAKE_CURRENT_LIST_DIR}/../third_party/doctest")
set(doctest_ROOT "${PROJECT_SOURCE_DIR}/lib/doctest")
set(doctest_INCLUDE_DIR "${doctest_ROOT}")
if(EXISTS "${doctest_ROOT}")
    set(doctest_FOUND ON)
endif()

add_library(doctest::doctest INTERFACE IMPORTED)
set_target_properties(doctest::doctest PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${doctest_INCLUDE_DIR}"
)
