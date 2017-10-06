#ifndef _JOB_H
#define _JOB_H

#include<sys/types.h>
#include<stdlib.h>
#include<vector>
using namespace std;

namespace gao
{
	const int OUTAPPEND = 3;
	const int OUTREDIRECT = 1;

	static int next_jobid = 1;

	enum class JobState {UNDEFINED = 0, FRONTGROUND, BACKGROUND, STOPPED};

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
		JobState state;
		vector<Command> commands;
		Job()
		{
			jobid = 0;
			pgid = 0;
			state = JobState::UNDEFINED;
		}
	};

	int get_front_job();

	int pid2jobid(pid_t pid);

	int pid2index(pid_t pid);
}

#endif