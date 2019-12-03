# ===========================================================================
# FIND: spdlog
# ===========================================================================
# NOTE: Bundled w/ project

# TOPDIR := "${CMAKE_CURRENT_LIST_DIR}/.."
set(spdlog_ROOT "${PROJECT_SOURCE_DIR}/lib/spdlog")
set(spdlog_INCLUDE_DIR "${spdlog_ROOT}/include")
if(EXISTS "${spdlog_ROOT}/CMakeLists.txt")
    set(spdlog_FOUND ON)
endif()
message(STATUS "XXX spdlog_FOUND=${spdlog_FOUND}")

# PREPARED: set(SPDLOG_BUILD_SHARED OFF)
set(SPDLOG_LIBRARY_TYPE "STATIC")
if(SPDLOG_BUILD_SHARED)
    set(SPDLOG_LIBRARY_TYPE  "SHARED")
endif()
add_library(spdlog::spdlog ${SPDLOG_LIBRARY_TYPE} IMPORTED)
set_target_properties(spdlog::spdlog PROPERTIES
    IMPORTED_INCLUDE_DIRECTORIES "${spdlog_INCLUDE_DIR}"
)
