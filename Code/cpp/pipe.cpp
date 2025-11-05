#include "command.h"
#include <iostream>
Pipe::~Pipe()// Destructor - clean up commands in pipe
{
	for (Command* cmd : m_commands)
	{
		delete cmd;
	}
}
void Pipe::addCommand(Command* cmd)// Add command to pipe
{
	m_commands.push_back(cmd);
}
void Pipe::execute()// Execute pipe - chain commands together
{
	int numOfCmd = m_commands.size();
	if (numOfCmd == 0)throw exception("Empty pipe command");
	for (int i = 0;i < numOfCmd - 1;i++)// Execute commands in sequence, passing output to next command
	{
		if (!m_commands[i])throw exception("Null command in pipe");
		m_commands[i]->setOutputStream(new StringOutputStream());
		m_commands[i]->execute();
		string curOutput = m_commands[i]->getOutputStream()->getContent();
		m_commands[i + 1]->setInputStream(new StringInputStream(curOutput));
	}
	m_commands[numOfCmd - 1]->execute();// Execute final command
}

string Pipe::getName() const // Get command name
{
	return "Pipe";
}

void Pipe::setInputStream(InputStream* in)// Set input for first command in pipe
{
	m_commands[0]->setInputStream(in);
}

void Pipe::setOutputStream(OutputStream* out)// Set output for last command in pipe
{
	m_commands[m_commands.size() - 1]->setOutputStream(out);
}
