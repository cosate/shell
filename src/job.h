#ifndef _JOB_H
#define _JOB_H

#include<sys/types.h>
#include<stdlib.h>
#include<vector>
using namespace std;

namespace gao
{
	enum class JobState {UNDEFINED = 0, FRONTGROUND, BACKGROUND, STOPPED};

	class Command
	{
	public:
		vector<char*> argv;
		int infd;
		int outfd;
		char* infile;
		char* outfile;
		Command()
		{
			infd = 0;
			outfd = 0;
			infile = NULL;
			outfile = NULL;
		}
	};

	class Job
	{
	public:
		int jobid;
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

	int pgid2jobid(pid_t);

	int pgid2index(pid_t);

	void list_jobs();

	void print_job(Job&);
}
#endif