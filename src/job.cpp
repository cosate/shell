#include<sys/types.h>
#include<vector>
#include"job.h"

using namespace gao;

extern vector<Job> jobs;

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

int pid2jobid(pid_t pid)
{
	int res = 0;
	for(; res < jobs.size(); res++)
	{
		if(jobs[res].pgid == pid)
			return res;
	}
	return -1;
}