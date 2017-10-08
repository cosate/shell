#include<sys/types.h>
#include<vector>
#include<stdio.h>
#include"job.h"

extern vector<gao::Job> jobs;

namespace gao
{
	int get_front_job()
	{
		int res = 0;
		for(; res < jobs.size(); res++)
		{
			if(jobs[res].state == JobState::FRONTGROUND)
				return res;
		}
		return -1;
	}

	int pgid2jobid(pid_t pid)
	{
		for(int res = 0; res < jobs.size(); res++)
		{
			if(jobs[res].pgid == pid)
				return jobs[res].jobid;
		}
		return -1;
	}

	int pgid2index(pid_t pid)
	{
		for(int i = 0; i < jobs.size(); i++)
		{
			if(jobs[i].pgid == pid)
				return i;
		}
		return -1;
	}

	void list_jobs()
	{
		for(auto it = jobs.begin(); it != jobs.end(); it++)
		{
			printf("[%d] (%d) ", it->jobid, it->pgid);
			if(it->state == JobState::FRONTGROUND)
				printf("Frontground");
			else if(it->state == JobState::BACKGROUND)
				printf("Background ");
			else if(it->state == JobState::STOPPED)
				printf("Stopped");
			else
				printf("Undefined");
			print_job(*it);
		}
	}

	void print_job(Job& job)
	{
		for(int i = 0; i < job.commands.size(); i++)
		{
			for(int j = 0; j < job.commands[i].argv.size(); j++)
			{
				printf("%s ", job.commands[i].argv[j]);
			}
			if(job.commands[i].infile != NULL)
				printf("<%s ", job.commands[i].infile);
			if(job.commands[i].outfile != NULL)
				printf(">>%s ", job.commands[i].outfile);
			printf("\n");
		}
	}
}