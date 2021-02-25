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

template <typename T>
std::ostream &printTo(std::ostream &os, const std::vector<T> &container)
{
    os << "[";
    for (const auto &item : container) {
        os << item << ", ";
    }
    os << "]";
    return os;
}

} // namespace doctest_ext

namespace std {

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &container)
{
    return doctest_ext::printTo(os, container);
}

} // namespace std

//< ENDOF(__TEST_HEADER_FILE__)
