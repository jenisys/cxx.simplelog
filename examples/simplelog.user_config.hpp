/**
 * @file simplelog.user_config.hpp
 * Example for an optional user-specific config-file for simplelog.
 **/
#pragma once

// #error "SIMPLELOG-USER-CONFIG: USED"
#ifndef SIMPLELOG_USE_BACKEND_SPDLOG
#define SIMPLELOG_USE_BACKEND_SPDLOG 1
#endif
// #define SIMPLELOG_DIAG 0
