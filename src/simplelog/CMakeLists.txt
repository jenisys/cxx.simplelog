# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog
# ===========================================================================

# ---------------------------------------------------------------------------
# SECTION: LIBS
# ---------------------------------------------------------------------------
# -- HEADER-ONLY LIBRARY:
add_library(simplelog INTERFACE)
add_library(${PROJECT_NAMESPACE}::simplelog ALIAS simplelog)
target_include_directories(
    simplelog INTERFACE $<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}> $<INSTALL_INTERFACE:include>
)
# -- SIMPLELOG DEFAULT-BACKEND:
# if(SIMPLELOG_USE_BACKEND_SPDLOG)
#     target_link_libraries(simplelog INTERFACE spdlog::spdlog)
#     set_target_properties(simplelog
#         PROPERTIES INTERFACE_COMPILE_DEFINITIONS
#             "SIMPLELOG_USE_BACKEND_SPDLOG=1"
#     )
# endif()
