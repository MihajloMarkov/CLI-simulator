#include "input_output.h"
#include<iostream>
string ConsoleInputStream::read()// Read input from console
{
    string data="", line;
    while (getline(cin, line))
    {
        data += line + "\n";
    }
    if (!data.empty())data.pop_back();
    cin.clear();
    return data;
}

string ConsoleInputStream::getType() const// Get stream type
{
    return "Console";
}

void ConsoleOutputStream::write(const string& content)// Write output to console
{
    cout << content << '\n';
}

string ConsoleOutputStream::getType() const// Get stream type
{
    return "Console";
}
