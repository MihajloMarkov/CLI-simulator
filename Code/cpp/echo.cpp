#include "command.h"
#include "input_output.h"
#include<iostream>

void EchoCommand::execute()// Execute echo command - outputs input text
{
	if (m_input && m_output)
	{
		m_output->write(m_input->read());
	}
	else throw exception("Missing input/output stream for echo command");
}


string EchoCommand :: getName() const// Get command name
{
	return "Echo";
}
