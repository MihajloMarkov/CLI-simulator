#include "command.h"
#include "input_output.h"
#include <sstream>
#include <iostream>

WCCommand::WCCommand(const string& option)// Constructor for wc command
{
	this->option = option;
}

void WCCommand::setOption(const string& option)// Set option for wc command
{
	this->option = option;
}

void WCCommand::execute()// Execute wc command
{
	if (!m_input || !m_output)throw exception("Missing input/output stream for wc command");
	string data = m_input->read();
	if (option == "-w") executew(data);
	else if (option == "-c")executec(data);
	else throw runtime_error("Invalid option for wc: " + option);
}

void WCCommand::executew(const string& data)// Execute word count
{
	stringstream ss(data);
	string word;
	int cnt = 0;
	while (ss >> word)cnt++;
	m_output->write(to_string(cnt));
}

void WCCommand::executec(const string& data)// Execute character count
{
	int cnt = data.length();
	m_output->write(to_string(cnt));
}

string WCCommand::getName() const// Get command name
{
	return "Wc";
}
