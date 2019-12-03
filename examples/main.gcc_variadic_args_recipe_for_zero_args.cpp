/**
 * @file main.gcc_variadic_args_recipe_for_zero_args.cpp
 * 
 * Simple example how a generic logging framework w/ different logging 
 * subsystems could look like.
 * 
 * @see https://github.com/gabime/spdlog
 * @see https://github.com/fmtlib/fmt
 **/

// -- INCLUDES:
#include <fmt/format.h>
#include <iostream>

// ==========================================================================
// DEFINE CPP MACROS
// ==========================================================================
// USING GCC-TRICK: Eat up preceeding COMMA if zero __VA_ARGS__ are used.
// SEE: 
//  * https://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick
//  * https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
//  * https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
// ALTERNATIVE SINCE C++2a: __VA_OPT__
// REQUIRES-COMPILER-OPTION: -Wno-gnu-zero-variadic-macro-arguments (for clang)
#define CXXLOG_1(format_, ...) \
    std::cout <<"CXXLOG_1: "<< fmt::format(format_, ## __VA_ARGS__) << std::endl

#define CXXLOG_2_STAGE1(format_, ...) \
    std::cout <<"CXXLOG_2: "<< fmt::format(format_, ## __VA_ARGS__) << std::endl
#define CXXLOG_2(format_, ...) CXXLOG_2_STAGE1(format_, ## __VA_ARGS__)

#define CXXLOG_3_STAGE2(format_, ...) \
    std::cout <<"CXXLOG_3: "<< fmt::format(format_, ## __VA_ARGS__) << std::endl
#define CXXLOG_3_STAGE1(format_, ...)   CXXLOG_3_STAGE2(format_, ## __VA_ARGS__)
#define CXXLOG_3(format_, ...)          CXXLOG_3_STAGE1(format_, ## __VA_ARGS__)


// ==========================================================================
// EXAMPLE: Use CPP Macros
// ==========================================================================
void example_useMacros1(void)
{
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    CXXLOG_1("ZERO_ARGS: Hello Alice");
    CXXLOG_1("ONE_ARG:   Hello {}", "Bob");
    CXXLOG_1("TWO_ARGS:  Hello {} and {}", "Alice", "Bob");
}

void example_useMacros2(void)
{
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    CXXLOG_2("ZERO_ARGS: Hello Alice");
    CXXLOG_2("ONE_ARG:   Hello {}", "Bob");
    CXXLOG_2("TWO_ARGS:  Hello {} and {}", "Alice", "Bob");
}

void example_useMacros3(void)
{
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    CXXLOG_3("ZERO_ARGS: Hello Alice");
    CXXLOG_3("ONE_ARG:   Hello {}", "Bob");
    CXXLOG_3("TWO_ARGS:  Hello {} and {}", "Alice", "Bob");
}

// ==========================================================================
// MAIN-FUNCTION:
// ==========================================================================
int main(int argc, char **argv)
{
    example_useMacros1();
    example_useMacros2();
    example_useMacros3();
    return EXIT_SUCCESS;
}
