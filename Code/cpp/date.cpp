#include "command.h"
#include "input_output.h"
#include <iostream>
#include <ctime>
#include <sstream>

void DateCommand::execute()// Execute date command - displays current date
{
    if (!m_output) throw exception("No output stream for date command");
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);
    stringstream ss;
    ss << (localTime.tm_year + 1900) << "-"
    << (localTime.tm_mon + 1 < 10 ? "0" : "") << (localTime.tm_mon + 1) << "-"
    << (localTime.tm_mday < 10 ? "0" : "") << localTime.tm_mday;
    string data = ss.str();
    m_output->write(data);
}

string DateCommand::getName() const // Get command name
{
	return "Date";
}
