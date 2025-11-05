#include "input_output.h"
#include <fstream>

FileInputStream::FileInputStream(const string& filename)// Constructor for file input stream
{
	this->filename = filename;
}

string FileInputStream::read()// Read content from file
{
	ifstream inputFile(filename);
	if (!inputFile.is_open())throw exception("File error, the file does not exist");;
	string content, line;
	while (getline(inputFile, line))
	{
		content += line + "\n";
	}
	if (!content.empty())content.pop_back();
	return content;
}

string FileInputStream::getType() const// Get stream type
{
	return "File";
}

FileOutputStream::FileOutputStream(const string& filename, bool append)// Constructor for file output stream
{
	this->filename = filename;
	this->append = append;
}

void FileOutputStream::write(const string& content)// Write content to file
{
	ofstream outputFile;
	if (append)outputFile.open(filename, ios::app);
	else outputFile.open(filename);
	if (outputFile)
	{
		outputFile << content;
	}
	else throw exception("File error, the file does not exist");
}

string FileOutputStream::getType() const// Get stream type
{
	return "File";
}
