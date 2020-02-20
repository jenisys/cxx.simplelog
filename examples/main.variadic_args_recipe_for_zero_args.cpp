/**
 * @file main.gcc_variadic_args_recipe_for_zero_args.cpp
 * Proof-of-concept for GNU variadic-macro trick with zero args.
 *
 * @par IMPLEMENTATION DETAIL: GNU CPP Preprocessor Variadic-Macro Trick
 * The GNU CPP Preprocessor variadic-macro trick with zero args is used here.
 * The trick eats up (deletes) a preceeding COMMA if zero __VA_ARGS__ are used.
 * @note TRICK: ", ## __VA_ARGS__"
 * @note NEEDS CXX COMPILER FLAG: -Wno-gnu-zero-variadic-macro-arguments
 * @since C++2a: __VA_OPT__ (as alternative)
 *
 * EXAMPLE:
 * @code
 *  #define DIAG_PRINT(format_, ...) fmt::print(format_, ## __VA_ARGS__)
 *
 *  DIAG_PRINT("__ZERO_ARGS__");
 *  DIAG_PRINT("__ONE_ARGS: {}}", "Alice");
 *  DIAG_PRINT("__TWO_ARGS: {} and {}}", "Alice", "Bob");
 * @endcode
 * @see
 *   *
 *https://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick
 *   * https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
 *   * https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
 **/

// -- INCLUDES:
#ifndef SIMPLELOG_DIAG__USE_SPDLOG_FMTLIB
#    define SIMPLELOG_DIAG__USE_SPDLOG_FMTLIB 0
#endif
#if SIMPLELOG_DIAG__USE_SPDLOG_FMTLIB
#    include <spdlog/fmt/fmt.h>
#else
#    include <fmt/format.h>
#endif
#include <iostream>

// ==========================================================================
// DEFINE CPP MACROS
// ==========================================================================
// USING GCC-TRICK: Eat up preceeding COMMA if zero __VA_ARGS__ are used.
// REQUIRES-COMPILER-OPTION: -Wno-gnu-zero-variadic-macro-arguments (for clang)
//
// DECISION: Avoid gnu-zero-variadic-macro-arguments trick
// REASON:
//  Has problems w/ g++ 8.x and CXX_STANDARD=11, 14, 17
//  ModernC++ (C++11 and newer) requires that macro(...) has at least one
//  parameter.
// ==========================================================================

#define USE_GNU_VARIADIC_MACRO_TRICK 0
#if USE_GNU_VARIADIC_MACRO_TRICK
#    define CXXLOG_1(format_, ...) std::cout << "CXXLOG_1: " << fmt::format(format_, ##__VA_ARGS__) << std::endl

#    define CXXLOG_2_STAGE1(format_, ...) std::cout << "CXXLOG_2: " << fmt::format(format_, ##__VA_ARGS__) << std::endl
#    define CXXLOG_2(format_, ...)        CXXLOG_2_STAGE1(format_, ##__VA_ARGS__)

#    define CXXLOG_3_STAGE2(format_, ...) std::cout << "CXXLOG_3: " << fmt::format(format_, ##__VA_ARGS__) << std::endl
#    define CXXLOG_3_STAGE1(format_, ...) CXXLOG_3_STAGE2(format_, ##__VA_ARGS__)
#    define CXXLOG_3(format_, ...)        CXXLOG_3_STAGE1(format_, ##__VA_ARGS__)

#else
// -- ALTERNATIVE: Without variadic-macro trick
// MACRO-SIGNATURE:
//  CXXLOG_1(message)       -- Simple cstring message w/o placeholders.
//  CXXLOG_1(format_, ...)  -- Format and placeholder values.
#    define CXXLOG_1(...) std::cout << "CXXLOG_1: " << fmt::format(__VA_ARGS__) << std::endl

#    define CXXLOG_2_STAGE1(...) std::cout << "CXXLOG_2: " << fmt::format(__VA_ARGS__) << std::endl
#    define CXXLOG_2(...)        CXXLOG_2_STAGE1(__VA_ARGS__)

#    define CXXLOG_3_STAGE2(...) std::cout << "CXXLOG_3: " << fmt::format(__VA_ARGS__) << std::endl
#    define CXXLOG_3_STAGE1(...) CXXLOG_3_STAGE2(__VA_ARGS__)
#    define CXXLOG_3(...)        CXXLOG_3_STAGE1(__VA_ARGS__)
#endif

// ==========================================================================
// EXAMPLE: Use CPP Macros
// ==========================================================================
void example_useMacros1(void)
{
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    CXXLOG_1("ZERO_ARGS: Hello");
    CXXLOG_1("ONE_ARG:   Hello {}", "Bob");
    CXXLOG_1("TWO_ARGS:  Hello {} and {}", "Alice", "Bob");
}

void example_useMacros2(void)
{
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    CXXLOG_2("ZERO_ARGS: Hello");
    CXXLOG_2("ONE_ARG:   Hello {}", "Bob");
    CXXLOG_2("TWO_ARGS:  Hello {} and {}", "Alice", "Bob");
}

void example_useMacros3(void)
{
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    CXXLOG_3("ZERO_ARGS: Hello");
    CXXLOG_3("ONE_ARG:   Hello {}", "Bob");
    CXXLOG_3("TWO_ARGS:  Hello {} and {}", "Alice", "Bob");
}

// ==========================================================================
// MAIN-FUNCTION:
// ==========================================================================
int main()
{
    example_useMacros1();
    example_useMacros2();
    example_useMacros3();
    return EXIT_SUCCESS;
}
