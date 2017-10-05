#ifndef _PARSE_H
#define _PARSE_H

#include<string>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<vector>
using namespace std;

const bool FRONTGROUND = true;
const bool BACKGROUND = false;
const int OUTAPPEND = 3;
const int OUTREDIRECT = 1;

struct Command
{
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

struct Job
{
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

void pass_whitespace(char*&);
int parse_jobs(string&, vector<Job>&);
int parse_job(char*&, vector<Job>&);
int parse_command(char*&, Job&);
int execute(Job&);

#endif