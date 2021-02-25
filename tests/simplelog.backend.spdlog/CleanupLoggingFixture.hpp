/**
 * @file tests/simplelog.backend.spdlog/CleanupLoggingFixture.hpp
 * @note REQUIRES: doctest >= 2.3.5
 * @author Jens Engel
 **/

// -- MORE-INCLUDES:
#include <spdlog/spdlog.h>

namespace tests {
namespace simplelog {
namespace backend_spdlog {

inline void cleanupLogging()
{
    ::spdlog::drop_all();
    // AVOID: ::spdlog::shutdown();
}

class CleanupLoggingFixture
{
public:
    CleanupLoggingFixture() { cleanupLogging(); }
    ~CleanupLoggingFixture() { cleanupLogging(); }
};

class CleanupLoggingBeforeFixture
{
public:
    CleanupLoggingBeforeFixture() { cleanupLogging(); }
};

class CleanupLoggingAfterFixture
{
public:
    ~CleanupLoggingAfterFixture() { cleanupLogging(); }
};

} // namespace backend_spdlog
} // namespace simplelog
} // namespace tests
//< ENDOF(__TEST_HEADER_FILE__)
