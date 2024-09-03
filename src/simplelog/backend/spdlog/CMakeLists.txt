# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/spdlog
# ===========================================================================

# ---------------------------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------------------------
if(NOT TARGET spdlog::spdlog)
    if(NOT DEFINED SPDLOG_MIN_VERSION)
        set(SPDLOG_MIN_VERSION "1.14.1")
    endif()
    find_package(spdlog ${SPDLOG_MIN_VERSION} REQUIRED)
endif()

# ---------------------------------------------------------------------------
# BACKEND-SPECIFIC LIBRARY: simplelog_spdlog (HEADER-ONLY, but spdlog is STATIC-LIBRARY)
# ---------------------------------------------------------------------------
# USED-FOR: Use simplelog library with configured simplelog.backend.spdlog.
add_library(simplelog_spdlog INTERFACE)
add_library(${PROJECT_NAMESPACE}::simplelog_spdlog ALIAS simplelog_spdlog)
target_link_libraries(simplelog_spdlog INTERFACE simplelog spdlog::spdlog)
set_target_properties(simplelog_spdlog
    PROPERTIES INTERFACE_COMPILE_DEFINITIONS
        "SIMPLELOG_USE_BACKEND_SPDLOG=1"
)
target_compile_features(simplelog_spdlog
    INTERFACE
        cxx_auto_type
        cxx_lambdas
        cxx_trailing_return_types
        cxx_variadic_macros
)
# -- INHERITED-FROM: simplelog
# target_include_directories(simplelog_spdlog
#     INTERFACE
#         $<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}>
#         $<INSTALL_INTERFACE:include>
# )
