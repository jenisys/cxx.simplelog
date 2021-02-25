/**
 * @file simplelog/detail/LogBackendMacros.hpp
 * Trampoline to include specific SIMPLELOG_BACKEND_xxx() macros
 * for the current SIMPLELOG_BACKEND.
 *
 * @see "simplelog/backend/xxx/LogBackendMacros.hpp"
 **/

#pragma once

// --------------------------------------------------------------------------
// SIMPLELOG BACKEND SELECTED: Include
// "simplelog/backend/.../LogBackendMacros.hpp"
// --------------------------------------------------------------------------
// EXAMPLE: SIMPLELOG_BACKEND_MACROS_HEADER_FILE =
// "simplelog/backend/null/LogBackendMacros.hpp"
#include "simplelog/detail/SelectLogBackend.hpp"
#include SIMPLELOG_BACKEND_MACROS_HEADER_FILE

#if SIMPLELOG_VERBOSE
#    include "simplelog/detail/StringifyMacro.hpp"
#    pragma message("SIMPLELOG_USE_BACKEND=" STRINGIFY(SIMPLELOG_USE_BACKEND))
#    pragma message("SIMPLELOG_BACKEND_MACROS_HEADER_FILE=" STRINGIFY(         \
        SIMPLELOG_BACKEND_MACROS_HEADER_FILE))
#endif

// -- OLD IMPLEMEMENTATION:
// #if (SIMPLELOG_USE_BACKEND == 0)
// #  include "simplelog/backend/null/LogBackendMacros.hpp"
// #elif (SIMPLELOG_USE_BACKEND == 1)
// #  include "simplelog/backend/spdlog/LogBackendMacros.hpp"
// #elif (SIMPLELOG_USE_BACKEND == 2)
// #  include "simplelog/backend/syslog/LogBackendMacros.hpp"
// #elif (SIMPLELOG_USE_BACKEND == 3)
// #  include "simplelog/backend/systemd_journal/LogBackendMacros.hpp"
// #else
// #  error "UNKNOWN: SIMPLELOG_USE_BACKEND" SIMPLELOG_USE_BACKEND
// #  include "simplelog/backend/null/LogBackendMacros.hpp"
// #endif

// -- ENDOF-HEADER-FILE
