#include "command.h"
#include<sstream>

HeadCommand::HeadCommand(int count)// Constructor for head command
{
	m_count = count;
}

void HeadCommand::execute()// Execute head command - displays first n lines
{
	if (!m_input || !m_output) throw exception("Missing input / output stream for head command");
	if (m_count < 0)throw runtime_error("Invalid line count: " + to_string(m_count));
	string input = m_input->read(),line;
	istringstream instream(input);
	ostringstream outstream;
	while (m_count > 0 && getline(instream, line))
	{
		outstream << line << '\n';
		m_count--;
	}
	m_output->write(outstream.str());// Get command name
}

string HeadCommand::getName() const 
{
	return "Head";
}
