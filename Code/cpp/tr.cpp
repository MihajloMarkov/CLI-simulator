#include "command.h"
#include <iostream>
TrCommand::TrCommand(const string& what, const string& with)// Constructor for tr command
{
	m_what = what;
	m_with = with;
}

void TrCommand::execute()// Execute tr command - replaces text
{
	if (!m_input || !m_output)throw exception("Missing input/output stream for tr command");
	if (m_what == "")// No replacement text specified
	{
		m_output->write(m_input->read());
		return;
	}
	string instr = m_input->read(), outstr = "";
	int curpos = 0, len = instr.size();
	while (curpos < len)// Search and replace text
	{
		if (instr[curpos] == m_what[0] && curpos + m_what.length() <= len)
		{
			bool match = true;
			for (int i = 0;i < m_what.length();i++)// Check for full match
			{
				if (instr[curpos + i] != m_what[i])
				{
					match = false;
					break;
				}
			}
			if (match)// Replace matched text
			{
				outstr += m_with;
				curpos += m_what.length();
			}
			else// No match, copy character
			{
				outstr += instr[curpos];
				curpos++;
			}
		}
		else
		{
			outstr += instr[curpos];
			curpos++;
		}
	}
	m_output->write(outstr);
}

string TrCommand::getName() const // Get command name
{
	return "Tr";
}
