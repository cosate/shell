#include<sys/types.h>
#include<vector>
#include<stdio.h>
#include<cstring>
#include"job.h"

extern std::vector<gao::Job> jobs;

namespace gao
{
	int Job::next_jid = 1;
	
	void Job::parse_cmdline()
	{
		char* ptr = this->cmdline;
		char* buf, *delim;
		int argc, i;
		for(i = 0; i <= MAXCMDNUM && (buf = strsep(&ptr, "|")); i++)
		{
			argc = 0;
			while(1)
			{
				pass_whitespace(buf);
				delim = strchr(buf, ' ');
				if(delim == NULL)
				{
					if(*buf)
						this->cmd[i].argv[argc++] = buf;
					break;
				}
				else
				{
					this->cmd[i].argv[argc++] = buf;
					*delim = '\0';
					buf = delim + 1;
				}
			}
		}

		if(*(this->cmd[i - 1].argv[argc - 1]) == '&')
			this->BACKGROUND = true;
		else if(this->cmd[i - 1].argv[argc - 1][strlen(this->cmd[i - 1].argv[argc - 1]) - 1] == '&')
		{
			this->BACKGROUND = true;
			this->cmd[i - 1].argv[argc - 1][strlen(this->cmd[i - 1].argv[argc - 1]) - 1] = '\0';
		}
		this->ncmd = i;
	}

	int get_front_job_index()
	{
		for(int res = 0; res < jobs.size(); res++)
		{
			if(jobs[res].state == JobState::FRONTGROUND)
				return res;
		}
		return 0;
	}

	int pid2jid(pid_t pid)
	{
		for(int res = 0; res < jobs.size(); res++)
		{
			if(jobs[res].pid == pid)
				return jobs[res].jid;
		}
		return 0;
	}

	int pid2index(pid_t pid)
	{
		for(int i = 0; i < jobs.size(); i++)
		{
			if(jobs[i].pid == pid)
				return i;
		}
		return -1;
	}

	int jid2index(int jid)
	{
		for(int i = 0; i < jobs.size(); i++)
		{
			if(jobs[i].jid == jid)
				return i;
		}
		return -1;
	}

	void list_jobs()
	{
		for(auto it = jobs.begin(); it != jobs.end(); it++)
		{
			printf("[%d] (%ld) ", it->jid, (long)it->pid);
			if(it->state == JobState::FRONTGROUND)
				printf("Frontground");
			else if(it->state == JobState::BACKGROUND)
				printf("Background ");
			else if(it->state == JobState::STOPPED)
				printf("Stopped");
			else
				printf("Undefined");

			printf("\t\t%s\n", it->cmdline);
		}
	}
}