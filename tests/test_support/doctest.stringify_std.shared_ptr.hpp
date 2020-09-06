/**
 * @file tests/doctest/doctest.stringify_container.hpp
  **/

#pragma once

// -- MORE-INCLUDES:
#include <string>
#include <sstream>   // -- DOCTEST-NEEDS: For CMAKE_BUILD_TYPE=Release
#include <vector>


// --------------------------------------------------------------------------
// DOCTEST SUPPORT:
// --------------------------------------------------------------------------
// -- DOCSTRING TO-STRING-CONVERSION HELPER:

namespace doctest_ext {

template<typename T>
std::ostream& printTo(std::ostream& os, const std::vector<T>& container)
{
    os << "[";
    for (const auto& item : container) {
        os << item <<", ";
    }
    os << "]";
    return os;
}

} //< NAMESPACE-END: doctest_ext

namespace std {

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& container)
    {
        return doctest_ext::printTo(os, container);
    }

}

//< ENDOF(__TEST_HEADER_FILE__)
