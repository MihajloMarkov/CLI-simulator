#include "command.h"
#include <iostream>
void ExitCommand::execute()// Execute exit command - terminates program
{
	m_output->write("Exiting program...");
}

string ExitCommand::getName() const// Get command name
{
	return "Exit";
}
