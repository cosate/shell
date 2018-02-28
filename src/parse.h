#ifndef _PARSE_H
#define _PARSE_H

#include<string>
#include"job.h"

namespace gao
{
	inline void pass_whitespace(char*& cmd)
	{
		while(*cmd != '\0' && *cmd == ' ')
			cmd++;
	}
	
	int parse_command(const char*);
}

#endif