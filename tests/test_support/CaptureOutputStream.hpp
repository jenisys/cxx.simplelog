/**
 * @file CaptureOutputStream.hpp
 * @author Jens Engel
 **/

#pragma once

// -- INCLUDES:
#include <sstream>
#include <iostream>
#include <string>

//! ScopeGuard to capture an output-stream
class CaptureOutputStream
{
private:
    std::stringstream m_captured;
    std::ostream& m_outputStream;
    std::streambuf* m_outputBufferPtr;

    void captureOutput(void)
    {
        if (m_outputBufferPtr == nullptr) {
            m_outputBufferPtr = m_outputStream.rdbuf();
            m_outputStream.rdbuf(m_captured.rdbuf());
        }
    }

public:
    CaptureOutputStream(std::ostream& outputStream = std::cout)
        : m_captured(),
          m_outputStream(outputStream),
          m_outputBufferPtr(nullptr)
    {
        captureOutput();
    }
    ~CaptureOutputStream(void)
    {
        restoreOutputStream();
    }


    bool isEnabled() const
    {
        return (m_outputBufferPtr != nullptr);
    }

    void restoreOutputStream(void)
    {
        if (m_outputBufferPtr != nullptr) {
            m_outputStream.rdbuf(m_outputBufferPtr);
            m_outputBufferPtr = nullptr;
        }
    }

    void enable()
    {
        captureOutput();
    }

    void disable()
    {
        restoreOutputStream();
    }

    //! Clear the captured output.
    void clear()
    {
        m_captured.str("");
    }

    std::string getOutput() const
    {
        return m_captured.str();
    }

    std::string str(void) const
    {
        return m_captured.str();
    }
};
