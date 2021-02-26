# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/spdlog
# ===========================================================================

# ---------------------------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------------------------
if(NOT TARGET spdlog::spdlog)
    find_package(spdlog ${SPDLOG_MIN_VERSION} REQUIRED)
endif()

# ---------------------------------------------------------------------------
# BACKEND-SPECIFIC LIBRARY: simplelog_spdlog (HEADER-ONLY, but spdlog is STATIC-LIBRARY)
# ---------------------------------------------------------------------------
# USED-FOR: Use simplelog library with configured simplelog.backend.spdlog.
add_library(simplelog_spdlog INTERFACE)
target_link_libraries(simplelog_spdlog INTERFACE ${PROJECT_NAMESPACE}::simplelog spdlog::spdlog)
target_compile_definitions(simplelog_spdlog INTERFACE SIMPLELOG_USE_BACKEND_SPDLOG=1)
target_compile_features(
    simplelog_spdlog INTERFACE cxx_auto_type cxx_lambdas cxx_trailing_return_types
                               cxx_variadic_macros
)
# -- INHERITED-FROM: simplelog
# target_include_directories(simplelog_spdlog
#     INTERFACE
#         $<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}>
#         $<INSTALL_INTERFACE:include>
# )

packageProject(
    NAME simplelog_spdlog
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAMESPACE}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${SIMPLELOG_INCLUDE_DIR}
    INCLUDE_DESTINATION include
    COMPATIBILITY SameMajorVersion
    DISABLE_VERSION_SUFFIX YES
    DEPENDENCIES "fmt ${FMT_MIN_VERSION}; spdlog ${SPDLOG_MIN_VERSION}"
)
