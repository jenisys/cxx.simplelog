/**
 * @file
 * Provides preprocessor macro to stringify something.
 **/

#pragma once

/**
 * @macro STRINGIFY(x)
 * Convert preprocessor symbol value into a cstring.
 **/
#define _STRINGIFY_IMPL(x) #x
#define STRINGIFY(x)       _STRINGIFY_IMPL(x)

// -- ENDOF-HEADER-FILE
