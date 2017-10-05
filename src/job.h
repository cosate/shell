#ifndef _JOB_H
#define _JOB_H

#include<sys/types.h>
#include<vector>
using namespace std;

const bool FRONTGROUND = true;
const bool BACKGROUND = false;
const int OUTAPPEND = 3;
const int OUTREDIRECT = 1;

class Command
{
public:
	vector<char*> argv;
	int in;
	int out;
	char* infile;
	char* outfile;
	Command()
	{
		in = 0;
		out = 0;
		infile = NULL;
		outfile = NULL;
	}
};

class Job
{
public:
	size_t jobid;
	pid_t pgid;
	bool workmode;
	vector<Command> commands;
	Job()
	{
		jobid = 0;
		pgid = 0;
		workmode = FRONTGROUND;
	}
};

#endif