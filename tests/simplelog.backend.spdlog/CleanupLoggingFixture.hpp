/**
 * @file tests/simplelog.backend.spdlog/CleanupLoggingFixture.hpp
 * @note REQUIRES: doctest >= 2.3.5
 * @author Jens Engel
 **/

// -- MORE-INCLUDES:
#include <spdlog/spdlog.h>

namespace tests { namespace simplelog { namespace backend_spdlog {

inline void cleanupLogging(void)
{
    ::spdlog::drop_all();
    // AVOID: ::spdlog::shutdown();
}

class CleanupLoggingFixture
{
public:
    CleanupLoggingFixture(void)  { cleanupLogging(); }
    ~CleanupLoggingFixture(void) { cleanupLogging(); }
};

class CleanupLoggingBeforeFixture
{
public:
    CleanupLoggingBeforeFixture(void)  { cleanupLogging(); }
};

class CleanupLoggingAfterFixture
{
public:
    ~CleanupLoggingAfterFixture(void) { cleanupLogging(); }
};

}}}
//< ENDOF(__TEST_HEADER_FILE__)
