#include "reader.h"
#include <iostream>
#include <sstream>
ConsoleReader::ConsoleReader(){}// Console reader constructor

ConsoleReader::~ConsoleReader(){}// Console reader destructor

string ConsoleReader::read()// Read all input from console
{
	stringstream ss;
	ss << cin.rdbuf();
	return ss.str();
}

string ConsoleReader::getNextLine()// Read next line from console
{
	if (cin.fail() || cin.eof())
	{
		cin.clear();
	}
	string line;
	if(!getline(cin, line))return "";
	if (line.length() > 512) return line.substr(0, 512);// Limit line length
	return line;
}

Reader::Reader(){}// Base reader constructor

Reader::~Reader(){}// Base reader destructor

FileReader::FileReader(string filepath)// File reader constructor
{
	m_input = new ifstream(filepath);
}

FileReader::~FileReader(){}// File reader destructor

string FileReader::read()// Read entire file content
{
	stringstream buffer;
	buffer << m_input->rdbuf();  
	return buffer.str();
}

string FileReader::getNextLine()// Read next line from file
{
	string line;
	if(!getline(*m_input, line))return "";
	return line;
}


Stringreader::Stringreader(string& data)// String reader constructor
{
	myData = data;
	ss.str(data);
}

string Stringreader::read()// Return stored string data
{
	return myData;
}

string Stringreader::getNextLine()// Read next line from string data
{
	string line;
	if(getline(ss, line))return line;
	return "";
}
