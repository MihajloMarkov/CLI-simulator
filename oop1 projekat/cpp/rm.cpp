#include "command.h"

void RmCommand::execute()// Execute remove command - deletes file
{
	if (!m_input) throw exception("No input stream for rm command");
	string filename = m_input->read();
	if (filename == "")throw exception("Missing filename for rm command");
	if (remove(filename.c_str()))throw exception("rm failed");
}

string RmCommand::getName() const // Get command name
{
	return "Rm";
}
