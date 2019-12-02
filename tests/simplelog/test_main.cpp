/**
 * @file tests/unit/test_main.cpp
 * Unit tests main-function by using the doctest C++ testing framework.
 *
 * @see https://github.com/onqtam/doctest
 * @see https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 **/

// -- TEST MAIN:
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"


// ==========================================================================
// DOCTEST EXTENSION: XML REPORTER (Blueprint only)
// ==========================================================================
// SEE: https://github.com/onqtam/doctest/blob/master/doc/markdown/reporters.md
namespace doctest_ext {

    using namespace doctest;

#if 0
    struct XmlReporter : public IReporter
    {
        std::ostream&                 s;
        std::vector<SubcaseSignature> subcasesStack;

        // caching pointers to objects of these types - safe to do
        const ContextOptions* opt;
        const TestCaseData*   tc;

        XmlReporter(std::ostream& in)
                : s(in) {}

        void test_run_start(const ContextOptions& o) override { opt = &o; }
        void test_run_end(const TestRunStats& /*p*/) override {}

        void test_case_start(const TestCaseData& in) override { tc = &in; }
        void test_case_end(const CurrentTestCaseStats& /*st*/) override {}

        void subcase_start(const SubcaseSignature& subc) override { subcasesStack.push_back(subc); }
        void subcase_end(const SubcaseSignature& /*subc*/) override { subcasesStack.pop_back(); }

        void log_assert(const AssertData& /*rb*/) override {}
        void log_message(const MessageData& /*mb*/) override {}

        void test_case_skipped(const TestCaseData& /*in*/) override {}
    };
#endif

} //< NAMESPACE-END: doctest_ext

namespace {
    using namespace doctest;

#if 0
    doctest_ext::XmlReporter xmlReporter4Doctest(std::cout);
    DOCTEST_REGISTER_REPORTER("xml", 1, xmlReporter4Doctest);
#endif
}

