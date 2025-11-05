#include "command.h"
#include <fstream>

void TruncateCommand::execute()// Execute truncate command - truncates file to zero length
{
	if (!m_input)throw exception("No input stream for truncate command");
	string filename = m_input->read();
	if (filename == "")throw exception("Missing filename for truncate command");
	ofstream file(filename, ios::trunc);
	if (!file)throw exception("Truncate failed");
}

string TruncateCommand::getName() const // Get command name
{
	return "Truncate";
}
