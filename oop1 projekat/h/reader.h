#ifndef _CITAC__
#define _CITAC__
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

class Reader {// Abstract reader class for different input sources
public:
	Reader();
	virtual ~Reader();
	virtual string read() = 0;
	virtual string getNextLine() = 0;
protected:

private:

};

class FileReader : public Reader {// File reader - reads from file
public:
	FileReader(string filepath);
	~FileReader();

	virtual string read();
	virtual string getNextLine();
protected:

private:
	ifstream* m_input=nullptr;
};

class ConsoleReader : public Reader {// Console reader - reads from console input
public:
	ConsoleReader();
	~ConsoleReader();

	virtual string read();
	virtual string getNextLine();
protected:

private:

};

class  Stringreader : public Reader {// String reader - reads from string data
public:
	Stringreader(string& data);
	virtual string read();
	virtual string getNextLine();
protected:

private:
	string myData;
	istringstream ss;
};

#endif 

