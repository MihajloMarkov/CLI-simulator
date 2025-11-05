#include "command.h"

Command::Command() = default;// Default constructor

Command::~Command() {// Destructor - clean up input/output streams
    delete m_input;
    delete m_output;
}

void Command::setInputStream(InputStream* in) // Set input stream for command
{
    if (m_input)
    {
        if (m_input->getType() != "Console")throw exception("Conflicting input streams, the command can't have two different input streams");
        delete m_input;
    }
    m_input = in;
}

void Command::setOutputStream(OutputStream* out)// Set output stream for command
{
    if (m_output)
    {
        if (m_output->getType() != "Console")throw exception("Conflicting output streams, the command can't have two different output streams");
        delete m_output;
    }
    m_output = out;
}

InputStream* Command::getInputStream() const// Get input stream
{
    return m_input;
}

OutputStream* Command::getOutputStream() const // Get output stream
{
    return m_output;
}