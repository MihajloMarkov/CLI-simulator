#include <iostream>
#include "simulator.h"
#include "command_parser.h"
#include "command.h"

int main()// Main program entry point
{
    Parser* parser = new Parser();  // Create command parser
    CLISimulator::instance()->prompt();  // Display initial prompt
    try
    {
        while (true)
        {

            Command* cmd = parser->getCommand();// Get next command
            if (!cmd)
            {
                CLISimulator::instance()->prompt();
                continue;
            }
            CLISimulator::instance()->simulate(cmd);// Execute command
            if (cmd->getName() == "Exit")break;// Exit on exit command
            CLISimulator::instance()->prompt();// Display prompt for next command
        }
    }
    catch(exception& e)// Handle exceptions
    {
        cout << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    catch (...)// Handle unknown exceptions
    {
        cout << "Unknown fatal error\n";
        return 2;
    }
    return 0;
}
