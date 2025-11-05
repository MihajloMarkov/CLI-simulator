#include <iostream>
#include "command.h"
#include "simulator.h"
#include "reader.h"
#include "command_parser.h"

void BatchCommand::execute() // Executes a batch of commands read from the input stream
{
	if (!m_input)throw exception("No input stream for batch command");
	string data = m_input->read();
	Stringreader* rdr = new Stringreader(data);
	Parser* parser = new Parser();
	string line = rdr->getNextLine();
	while (line != "")// Process each line until empty line or exit command
	{
		try
		{
			Command* cmd = parser->parseCommand(line);
			if (cmd->getName() == "Exit")
			{
				delete cmd;
				break;
			}
			CLISimulator::instance()->simulate(cmd);
			delete cmd;
		}
		catch (exception& e)
		{
			cout << e.what() << "\n";
		}
		line = rdr->getNextLine();
	}
	delete parser;
}

string BatchCommand::getName() const // Returns the name of this command
{
	return "Batch";
}
