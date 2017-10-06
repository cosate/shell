#include<sys/types.h>
#include<vector>
#include"job.h"

namespace gao
{
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
		for(int res = 0; res < jobs.size(); res++)
		{
			if(jobs[res].pgid == pid)
				return jobs[res].jobid;
		}
		return -1;
	}

	int pid2index(pid_t pid)
	{
		for(int i = 0; i < jobs.size(); i++)
		{
			if(jobs[i].pgid == pid)
				return i;
		}
		return -1;
	}
}