#pragma once
/**
 * @file
 * Provides preprocessor macro to stringify something.
 **/


/**
 * @macro STRINGIFY(x)
 * Convert preprocessor symbol value into a cstring.
 **/
#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)

// -- ENDOF-HEADER-FILE
