#include "command_parser.h"
#include<sstream>
#include<iostream>
#include "command.h"

Parser::Parser()// Default to console reader
{
	m_reader = new ConsoleReader(); 
}

Parser::Parser(Reader* rdr) : m_reader(rdr) {} // Constructor with custom reader

Parser::~Parser()
{
	delete m_reader; // Clean up reader
}

Command* Parser::getCommand() // Gets next command from input
{
	try
	{
		string line = m_reader->getNextLine();
		if (line == "")return nullptr;
		return parseCommand(line);
	}
	catch (exception& e)
	{
		cout << e.what() << "\n";
	}
	return nullptr;
}

void Parser::setReader(Reader* newReader) // Set new input reader
{
	if (m_reader) delete m_reader;
	m_reader = newReader;
}

Command* Parser::parseCommand(string& data)// Parse command from input string
{
	Command* cmd;
	if (containsCharacter(data, '|'))cmd = parsePipe(data);
	else cmd = parseSingleCommand(data);
	return cmd;
}

Command* Parser::parseSingleCommand(string& data)// Parse single command without pipes
{
	if (!quotesCheck(data)) throw exception("Unbalanced quotes");
	string inFile = "", outFile = "";
	bool append = false;
	if (containsCharacter(data, '<'))parseInputRedirection(data, inFile, outFile, append);// Handle input redirection
	if (containsCharacter(data, '>'))parseOutputRedirection(data, inFile, outFile, append);// Handle output redirection
	stringstream s(data);
	string cmdname = "";
	s >> cmdname;
	if (cmdname == "")throw exception("Missing command name");
	Command* cmd = nullptr;
	if (cmdname == "time") cmd = parseTime();
	else if (cmdname == "date") cmd = parseDate();
	else if (cmdname == "wc") cmd = parseWc(s);
	else if (cmdname == "touch") cmd = parseTouch(s);
	else if (cmdname == "echo") cmd = parseEcho(s);
	else if (cmdname == "exit") cmd = parseExit();
	else if (cmdname == "prompt") cmd = parsePrompt(s);
	else if (cmdname == "truncate") cmd = parseTruncate(s);
	else if (cmdname == "rm") cmd = parseRm(s);
	else if (cmdname == "tr") cmd = parseTr(s);
	else if (cmdname == "head") cmd = parseHead(s);
	else if (cmdname == "batch") cmd = parseBatch(s);
	else throw runtime_error("Unknown command: " + cmdname);
	skipSpaces(s);
	if (s.peek() != EOF)
	{
		string remaining = "";
		getline(s, remaining);
		throw runtime_error("Unknown command argument: " + remaining);
	}
	applyRedirection(cmd, inFile, outFile, append);
	return cmd;
}

Command* Parser::parseTime()// Parse time command
{
	TimeCommand* cmd = new TimeCommand();
	configureCommandStreams(cmd, ""); 
	return cmd;
}

Command* Parser::parseDate()// Parse date command
{
	DateCommand* cmd = new DateCommand();
	configureCommandStreams(cmd, ""); 
	return cmd;
}


Command* Parser::parseTouch(stringstream& data)// Parse touch command
{
	string filename = extractArgument(data);
	if (filename == "") throw exception("Missing file name for touch command");
	TouchCommand* cmd = new TouchCommand();
	cmd->setInputStream(new StringInputStream(filename));
	return cmd;
}

Command* Parser::parseWc(stringstream& data)// Parse wc command
{
	string option = extractArgument(data);
	if (!isOptionValid(option, { "-w","-c" }))throw runtime_error("Invalid option for wc: " + option);
	WCCommand* cmd = new WCCommand(option);
	string argument = extractArgument(data);
	configureCommandStreams(cmd, argument);
	return cmd;
}

Command* Parser::parseEcho(stringstream& data)// Parse echo command
{
	string argument = extractArgument(data);
	EchoCommand* cmd = new EchoCommand();
	configureCommandStreams(cmd, argument);
	return cmd;
}

Command* Parser::parseExit()// Parse exit command
{
	ExitCommand* cmd = new ExitCommand();
	configureCommandStreams(cmd, "");
	return cmd;
}

Command* Parser::parsePrompt(stringstream& data)// Parse prompt command
{
	string newprompt = extractArgument(data);
	stringstream ss(newprompt);
	newprompt = extractQuotedString(ss);
	PromptCommand* cmd = new PromptCommand();
	cmd->setInputStream(new StringInputStream(newprompt));
	return cmd;
}

Command* Parser::parseTruncate(stringstream& data)// Parse truncate command
{
	string filename = extractArgument(data);
	if (filename == "")throw exception("Missing file name for truncate command");
	TruncateCommand* cmd = new TruncateCommand();
	cmd->setInputStream(new StringInputStream(filename));
	return cmd;
}

Command* Parser::parseTr(stringstream& data)// Parse tr command
{
	string arg1 = extractArgument(data), arg2 = extractArgument(data), arg3 = extractArgument(data), argument = "", what = "", with = "";
	if (arg1 == "")throw exception("Missing arguments for tr command");
	else if (arg2 == "")
	{
		stringstream ss(arg1);
		what = extractQuotedString(ss);
	}
	else if (arg3 == "")
	{
		if (arg1[0] != '"')
		{
			argument = arg1;
			stringstream ss(arg2);
			what = extractQuotedString(ss);
		}
		else
		{
			stringstream ss1(arg1);
			stringstream ss2(arg2);
			what = extractQuotedString(ss1);
			with = extractQuotedString(ss2);
		}
	}
	else
	{
		argument = arg1;
		stringstream ss1(arg2);
		stringstream ss2(arg3);
		what = extractQuotedString(ss1);
		with = extractQuotedString(ss2);
	}
	Command* cmd = new TrCommand(what, with);
	configureCommandStreams(cmd, argument);
	return cmd;
}

Command* Parser::parseRm(stringstream& data)// Parse rm command
{
	string filename = extractArgument(data);
	if (filename == "")throw exception("Missing file name for rm command");
	RmCommand* cmd = new RmCommand();
	cmd->setInputStream(new StringInputStream(filename));
	return cmd;
}

Command* Parser::parseHead(stringstream& data)// Parse head command
{
	string cnt = extractArgument(data);
	string arg = extractArgument(data);
	if (cnt.length() <= 2)throw runtime_error("invalid argument: " + cnt);
	if (cnt[0] != '-' || cnt[1] != 'n')throw runtime_error("Invalid option for head " + string(1, cnt[0]) + string(1, cnt[1]));
	if (cnt.length() > 7)throw runtime_error("Invalid line count: " + cnt.substr(2));
	for (int i = 2;i < cnt.length();i++)
	{
		if (!(cnt[i] <= '9' && cnt[i] >= '0'))throw runtime_error("Invalid line count: " + cnt.substr(2));
	}
	int lineCount = stoi(cnt.substr(2));
	if (lineCount <= 0)throw exception("Line count must be positive");
	HeadCommand* cmd = new HeadCommand(lineCount);
	configureCommandStreams(cmd, arg);
	return cmd;
}

Command* Parser::parseBatch(stringstream& data)// Parse batch command
{
	string argument = extractArgument(data);
	BatchCommand* cmd = new BatchCommand();
	configureCommandStreams(cmd, argument);
	return cmd;
}

Command* Parser::parsePipe(string& data)// Parse pipe command
{
	vector<string> commands = splitCommands(data, '|');
	if (commands.size() == 0)return nullptr;
	Pipe* pipecmd = new Pipe();
	for (string& s : commands)
	{
		Command* curcmd = parseSingleCommand(s);
		if (!curcmd)throw exception("Invalid command in pipe");
		pipecmd->addCommand(curcmd);
	}
	return pipecmd;
}


void Parser::skipSpaces(stringstream& data)// Skip whitespace in stream
{
	char c = data.peek();
	while (c == ' ' || c == '\t')c = data.get();
	if (c != EOF)data.unget();
}

string Parser::extractQuotedString(std::stringstream& data)// Extract quoted string from stream
{
	char c;
	data >> c;
	if (c != '"')
	{
		data.unget();
		return "";
	}
	string content;
	while (data.get(c))
	{
		if (c == '"')break;
		content += c;
	}
	return content;
}

string Parser::extractArgument(std::stringstream& data)// Extract argument from stream
{
	string content = "";
	skipSpaces(data);
	if (data.peek() == '"')content = '"' + extractQuotedString(data) + '"';
	else data >> content;
	return content;
}

string Parser::getNextWord(const string& line, int& startind)// Get next word from string
{
	while (startind < line.length() && (line[startind] == ' ' || line[startind] == '\t'))
	{
		startind++;
	}
	string nextword = "";
	while (startind < line.length() && !(line[startind] == ' ' || line[startind] == '\t'))
	{
		nextword += line[startind];
		startind++;
	}
	return nextword;
}

vector<string> Parser::splitCommands(const string& line, char delimiter)// Split commands by delimiter
{
	vector<string> commands;
	string curstr = "";
	bool inquotes = false;
	for (char c : line)
	{
		if (!inquotes && c == delimiter)
		{
			commands.push_back(curstr);
			curstr = "";
		}
		else
		{
			if (c == '"')inquotes = !inquotes;
			curstr += c;
		}
	}
	if (curstr.length() > 0)commands.push_back(curstr);
	return commands;
}

bool Parser::isOptionValid(const string& option, const vector<string>& validOptions)// Check if option is valid
{
	for (const string& valop : validOptions)
	{
		if (option == valop) return true;
	}
	return false;
}

bool Parser::containsCharacter(const string& line, char target)// Check if line contains character outside quotes
{
	bool inquotes = false;
	for (char c : line)
	{
		if (c == target && !inquotes)return true;
		else if (c == '"')inquotes = !inquotes;
	}
	return false;
}

void Parser::applyRedirection(Command* cmd, const string& inFile, const string& outFile, bool append)// Apply redirection to command
{
	if (inFile != "")cmd->setInputStream(new FileInputStream(inFile));
	if (outFile != "")cmd->setOutputStream(new FileOutputStream(outFile, append));
}

void Parser::parseInputRedirection(string& line, string& inFile, string& outFile, bool& append)// Parse input redirection
{
	if (inFile != "")throw exception("Only one redirection at the end is allowed");
	int len = line.length(), startind;
	bool inquotes = false;
	for (int i = 0;i < len;i++)
	{
		if (line[i] == '"')inquotes = !inquotes;
		else if (!inquotes && line[i] == '<')
		{
			startind = i;
			i++;
			inFile = getNextWord(line, i);
			if (inFile == "")throw exception("Missing file for input redirection");
			line.erase(startind, i - startind);
			break;
		}
	}
	int newlen = line.length();
	for (int i = startind;i < newlen;i++)
	{
		if (line[i] == '>')
		{
			parseOutputRedirection(line, inFile, outFile, append);
			break;
		}
		else if (line[i] != ' ' && line[i] != '\t')throw exception("Only one redirection at the end is allowed");
	}
	newlen = line.length();
	for (int i = startind;i < newlen;i++)
	{
		if (line[i] != ' ' && line[i] != '\t')throw exception("Only one redirection at the end is allowed");
	}

}

void Parser::parseOutputRedirection(string& line, string& inFile, string& outFile, bool& append)// Parse output redirection
{
	if (outFile != "")throw exception("Only one redirection at the end is allowed");
	int len = line.length(), startind;
	bool inquotes = false;
	for (int i = 0;i < len;i++)
	{
		if (line[i] == '"')inquotes = !inquotes;
		else if (!inquotes && line[i] == '>')
		{
			startind = i;
			i++;
			if (line[i] == '>')
			{
				append = true;
				i++;
			}
			outFile = getNextWord(line, i);
			if (outFile == "")throw exception("Missing file for output redirection");
			line.erase(startind, i - startind);
			break;
		}
	}
	int newlen = line.length();
	for (int i = startind;i < newlen;i++)
	{
		if (line[i] == '<')
		{
			parseInputRedirection(line, inFile, outFile, append);
			break;
		}
		else if (line[i] != ' ' && line[i] != '\t')throw exception("Only one redirection at the end is allowed");
	}
	newlen = line.length();
	for (int i = startind;i < newlen;i++)
	{
		if (line[i] != ' ' && line[i] != '\t')throw exception("Only one redirection at the end is allowed");
	}
}


InputStream* Parser::createInputStreamForArgument(const string& arg) // Create input stream for argument
{
	if (arg.empty())return new ConsoleInputStream();
	if (arg[0] == '"' && arg[arg.length() - 1] == '"')return new StringInputStream(arg.substr(1, arg.size() - 2));
	return new FileInputStream(arg);
}

void Parser::configureCommandStreams(Command* cmd, const string& arg) // Configure command input/output streams
{
	cmd->setInputStream(createInputStreamForArgument(arg));
	cmd->setOutputStream(new ConsoleOutputStream()); 
}

bool Parser::quotesCheck(string& data)// Check if quotes are balanced
{
	int qoutecnt = 0;
	for (char c : data)
	{
		if (c == '"')qoutecnt++;
	}
	if (qoutecnt % 2 != 0)return false;
	return true;
}

