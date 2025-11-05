#ifndef _KMDPRS__
#define _KMDPRS__
#include "reader.h"
#include <vector>

class Command;
class InputStream;
// Parser class for interpreting input commands
class Parser {
public:
	Parser();  // Default constructor
	explicit Parser(Reader* rdr);  // Constructor with custom reader
	~Parser();  // Destructor

	virtual Command* getCommand();  // Get next command from input
	virtual Command* parseCommand(string& data);  // Parse command from string data
	void setReader(Reader* newReader);  // Set new input reader
	
protected:
	// Command parsing methods for specific command types
	virtual Command* parseSingleCommand(string& data);  // Parse single command
	virtual Command* parseTime();  // Parse time command
	virtual Command* parseDate();  // Parse date command
	virtual Command* parseTouch(stringstream& data);  // Parse touch command
	virtual Command* parseWc(stringstream& data);  // Parse word count command
	virtual Command* parseEcho(stringstream& data);  // Parse echo command
	virtual Command* parseExit();  // Parse exit command
	virtual Command* parsePrompt(stringstream& data);  // Parse prompt command
	virtual Command* parseTruncate(stringstream& data);  // Parse truncate command
	virtual Command* parseTr(stringstream& data);  // Parse translate (tr) command
	virtual Command* parseRm(stringstream& data);  // Parse remove command
	virtual Command* parseHead(stringstream& data);  // Parse head command
	virtual Command* parseBatch(stringstream& data);  // Parse batch command

	virtual Command* parsePipe(string& data);  // Parse pipe command

	// Utility methods for parsing
	virtual void skipSpaces(stringstream& data);  // Skip whitespace in stream
	string extractQuotedString(stringstream& data);  // Extract quoted string
	string extractArgument(stringstream& data);  // Extract argument from stream
	string getNextWord(const string& line, int& startind);  // Get next word from string
	vector<string> splitCommands(const string& line, char delimiter);  // Split commands by delimiter
	bool isOptionValid(const string& option, const vector<string>& validOptions);  // Validate option
	bool containsCharacter(const string& line, char target);  // Check for character outside quotes
	void applyRedirection(Command* cmd, const string& inFile, const string& outFile, bool append);  // Apply redirection
	void parseInputRedirection(string& line, string& inFile, string& outFile, bool& append);  // Parse input redirection
	void parseOutputRedirection(string& line, string& inFile, string& outFile, bool& append);  // Parse output redirection
	InputStream* createInputStreamForArgument(const string& arg);  // Create input stream for argument
	void configureCommandStreams(Command* cmd, const string& arg = "");  // Configure command streams
	bool quotesCheck(string& data);  // Check for balanced quotes
	
private:
	Reader* m_reader;  // Input reader
};
#endif 

