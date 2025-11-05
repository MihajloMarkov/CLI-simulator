#include "input_output.h"

StringInputStream::StringInputStream(const string& data)// Constructor for string input stream
{
	this->data = data;
}

string StringInputStream::read()// Read from string input stream
{
	return data;
}

string StringInputStream::getType() const// Get stream type
{
	return "String";
}

void StringOutputStream::write(const string& content)// Write to string output stream
{
	outString = content;
}

string StringOutputStream::getContent() const// Get content from string output stream
{
	return outString;
}

string StringOutputStream::getType() const// Get stream type
{
	return "String";
}
