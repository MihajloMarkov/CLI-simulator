#include "command.h"
#include "input_output.h"
#include "simulator.h"
#include<iostream>

void PromptCommand::execute()// Execute prompt command - changes CLI prompt
{
	if (!m_input)throw exception("No input stream for prompt command");
	CLISimulator::instance()->setPrompt(m_input->read());
}

string PromptCommand::getName() const// Get command name
{
	return "Prompt";
}

