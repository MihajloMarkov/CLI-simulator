#include "command.h"
#include "input_output.h"
#include <iostream>


void TouchCommand::execute()// Execute touch command - creates empty file
{
	if (!m_input) throw exception("No input stream for touch command");
	string filename = m_input->read();
	if (filename == "")throw exception("Missing filename for touch command");
	FILE* exists = fopen(filename.c_str(), "r");
	if (exists)
	{
		fclose(exists);
		throw exception("File already exists");
	}
	else
	{
		FILE *f = fopen(filename.c_str(), "w");
		if (!f)throw exception("File creation failed");
		fclose(f);
	}
}

string TouchCommand::getName() const // Get command name
{
	return "Touch";
}
