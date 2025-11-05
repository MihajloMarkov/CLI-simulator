#include "simulator.h"
#include "command.h"
#include<iostream>

CLISimulator::CLISimulator(){}// CLI simulator constructor

CLISimulator::~CLISimulator(){}// CLI simulator destructor

CLISimulator* CLISimulator::instance()// Get singleton instance
{
	static CLISimulator simulator; // Static instance
	return &simulator;
}

void CLISimulator::simulate(Command* command)// Simulate command execution
{
	if (command)
	{
		try
		{
			command->execute();
		}
		catch(exception& e)
		{
			cout << "Command error: " << e.what() << "\n";
		}
	}
}

void CLISimulator::prompt()// Display command prompt
{
	cout << this->commandPrompt;
}

void CLISimulator::setPrompt(string newCmdPrompt)// Set new command prompt
{
	this->commandPrompt = newCmdPrompt;
}

string CLISimulator::getpromt()// Get current command prompt
{
	return commandPrompt;
}
