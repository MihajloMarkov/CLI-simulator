#ifndef _CLI__
#define _CLI__
#include <string>

class Command;

using namespace std;
// CLI simulator - manages program flow to simulate command line
class CLISimulator {
public:
	static CLISimulator* instance();  // Get singleton instance
	void simulate(Command* command);  // Execute command
	void prompt();  // Display command prompt
	void setPrompt(string newCmdPrompt);  // Set new prompt
	string getpromt();  // Get current prompt
protected:
	CLISimulator();  // Constructor
	~CLISimulator();  // Destructor
private:
	string commandPrompt = "$";  // Default prompt
};
#endif 

