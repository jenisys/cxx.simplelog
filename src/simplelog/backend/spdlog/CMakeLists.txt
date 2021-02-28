# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/spdlog
# ===========================================================================

# ---------------------------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------------------------
# if(NOT TARGET spdlog::spdlog)
#     find_package(spdlog ${SPDLOG_MIN_VERSION} REQUIRED)
# endif()

# ---------------------------------------------------------------------------
# BACKEND-SPECIFIC LIBRARY: simplelog_spdlog (HEADER-ONLY, but spdlog is STATIC-LIBRARY)
# ---------------------------------------------------------------------------
# USED-FOR: Use simplelog library with configured simplelog.backend.spdlog.
add_library(simplelog_spdlog INTERFACE)
target_link_libraries(
    simplelog_spdlog INTERFACE ${PROJECT_NAMESPACE}::simplelog
    # XXX $<BUILD_INTERFACE:spdlog::spdlog_header_only>
    spdlog::spdlog
)
target_compile_definitions(
    simplelog_spdlog INTERFACE SIMPLELOG_USE_BACKEND_SPDLOG=1
)
target_compile_features(
    simplelog_spdlog INTERFACE cxx_auto_type cxx_lambdas
                               cxx_trailing_return_types cxx_variadic_macros
)
# -- INHERITED-FROM: simplelog
# target_include_directories(simplelog_spdlog
#     INTERFACE
#         $<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}>
#         $<INSTALL_INTERFACE:include>
# )

# install the target and create export-set
if(ON)
    add_library(${PROJECT_NAMESPACE}::simplelog_spdlog ALIAS simplelog_spdlog)
    install(
        TARGETS simplelog_spdlog spdlog
        EXPORT ${PROJECT_NAMESPACE}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES
        DESTINATION include
    )
else()
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
endif()
