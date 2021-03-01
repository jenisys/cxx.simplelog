/**
 * @file CaptureOutputStream.hpp
 * @author Jens Engel
 **/

#pragma once

// -- INCLUDES:
#include <iostream>
#include <sstream>
#include <string>

//! ScopeGuard to capture an output-stream
class CaptureOutputStream
{
private:
    std::stringstream m_captured;
    std::ostream &m_outputStream;
    std::streambuf *m_outputBufferPtr{nullptr};

    void captureOutput()
    {
        if (m_outputBufferPtr == nullptr) {
            m_outputBufferPtr = m_outputStream.rdbuf();
            m_outputStream.rdbuf(m_captured.rdbuf());
        }
    }

public:
    explicit CaptureOutputStream(std::ostream &outputStream = std::cout) : m_outputStream(outputStream)
    {
        captureOutput();
    }
    ~CaptureOutputStream() { restoreOutputStream(); }

    auto isEnabled() const -> bool { return (m_outputBufferPtr != nullptr); }

    void restoreOutputStream()
    {
        if (m_outputBufferPtr != nullptr) {
            m_outputStream.rdbuf(m_outputBufferPtr);
            m_outputBufferPtr = nullptr;
        }
    }

    void enable() { captureOutput(); }

    void disable() { restoreOutputStream(); }

    //! Clear the captured output.
    void clear() { m_captured.str(""); }

    auto getOutput() const -> std::string { return m_captured.str(); }

    auto str() const -> std::string { return m_captured.str(); }
};
