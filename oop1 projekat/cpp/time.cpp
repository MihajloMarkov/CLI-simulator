#include "command.h"
#include "input_output.h"
#include <ctime>
#include <iostream>
#include <sstream>

void TimeCommand::execute()// Execute time command - displays current time
{
    if (!m_output) throw exception("No output stream for time command");
    time_t now = time(0); 
    tm localTime;  
    localtime_s(&localTime, &now);  
    stringstream ss;
    ss << (localTime.tm_hour < 10 ? "0" : "") << localTime.tm_hour << ":"
        << (localTime.tm_min < 10 ? "0" : "") << localTime.tm_min << ":"
        << (localTime.tm_sec < 10 ? "0" : "") << localTime.tm_sec;
    string data = ss.str();
    m_output->write(data);
}

string TimeCommand::getName() const// Get command name
{
	return "Time";
}
