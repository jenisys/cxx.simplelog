/**
 * @file simplelog.user_config.hpp
 * Example for an optional user-specific config-file for simplelog.
 **/
#pragma once

// -- WARNING:
// Only specify the SIMPLELOG_DEFAULT_BACKEND and not SIMPLELOG_USE_BACKEND.
// Otherwise you run into problem if you want to use multiple backends
// for different programs.
#ifndef SIMPLELOG_DEFAULT_BACKEND_MACROS_HEADER_FILE
#   define SIMPLELOG_DEFAULT_BACKEND_MACROS_HEADER_FILE  "simplelog/backend/spdlog/LogBackendMacros.hpp"
#   define SIMPLELOG_DEFAULT_BACKEND  1  //< SIMPLELOG_USE_BACKEND_SPDLOG
#endif

// -- AVOID: See explaination above.
// #ifndef SIMPLELOG_USE_BACKEND
// #define SIMPLELOG_BACKEND_MACROS_HEADER_FILE  "simplelog/backend/spdlog/LogBackendMacros.hpp"
// #define SIMPLELOG_USE_BACKEND_SPDLOG 1
// #endif

//< HEADER-FILE-END
