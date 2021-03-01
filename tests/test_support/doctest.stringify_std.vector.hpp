/**
 * @file tests/doctest/doctest.stringify_container.hpp
 **/

#pragma once

// -- MORE-INCLUDES:
#include <sstream> // -- DOCTEST-NEEDS: For CMAKE_BUILD_TYPE=Release
#include <string>
#include <vector>

// --------------------------------------------------------------------------
// DOCTEST SUPPORT:
// --------------------------------------------------------------------------
// -- DOCSTRING TO-STRING-CONVERSION HELPER:

namespace doctest_ext {

template <typename T> auto printTo(std::ostream &os, const std::vector<T> &container) -> std::ostream &
{
    os << "[";
    for (const auto &item : container) {
        os << item << ", ";
    }
    os << "]";
    return os;
}

} // namespace doctest_ext

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std { // FIXME: warning: modification of 'std' namespace can result in
                // undefined behavior [cert-dcl58-cpp]

template <typename T>
auto operator<<(std::ostream &os, const std::vector<T> &container) -> std::ostream &
{
    return doctest_ext::printTo(os, container);
}

} // namespace std

//< ENDOF(__TEST_HEADER_FILE__)
