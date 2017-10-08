#include<iostream>
#include<sys/types.h>
#include<errno>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include"execute.h"
#include"job.h"
#include"sig.h"
using namespace std;

extern vector<gao::Job> jobs;

namespace gao
{
	extern int OUTAPPEND;
	extern int OUTREDIRECT;

	void redirect(Command& command)
	{
		mode_t perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
		if(command.infile != NULL)
			command.infd = open(command.infile, O_RDONLY, perm);
		else
			command.infd = STDIN_FILENO;
		if(command.outfile != NULL)
		{
			if(commamd.outfd == OUTAPPEND)
				command.outfd = open(command.outfile, O_WRONLY | O_APPEND | O_CREAT, perm);
			else
				command.outfd = open(command.outfile, O_WRONLY | O_TRUNC | O_CREAT, perm);
		}
		else
			command.outfd = STDOUT_FILENO;

		if(command.infd != STDIN_FILENO)
		{
			dup2(command.infd, STDIN_FILENO);
			close(command.infd);
		}
		if(command.outfd != STDOUT_FILENO)
		{
			dup2(command.outfd, STDOUT_FILENO)
			close(command.outfd);
		}
	}
	void execute(Job& job)
	{
		signal_mask(SIG_BLOCK, SIGCHLD);
		pid_t pid;
		if(job.commands.size() == 1)
		{
			if(build_in(job))
			{
				signal_mask(SIG_UNBLOCK, SIGCHLD);
				return;
			}
			else
				pid = execute_single_job(job);
		}
		else
			pid = execute_pipe(job);

		jobs.push_back(job);
		if(job.state == JobState::FRONTGROUND)
			wait_front_job(pid);
		else
		{
			printf("[%d] (%d)", pid2jobid(pid), pid);
			print_job(job);
			signal_mask(SIG_UNBLOCK, SIGCHLD);
		}
	}

	pid_t execute_single_command(Job& job)
	{
		int argc = job.commands.size();
		char** argv = new char*[argc];
		for(int i = 0; i < argc; i++)
			argv[i] = job.commands[i];
		pid_t pid = fork();
		if(pid == -1)
		{
			cerr<<"fork error"<<endl;
		}
		else if(pid == 0)
		{
			
		}
		else
		{

		}
	}

	pid_t execute_pipe(Job& job)
	{

	}

	int build_in(Job& job)
	{
		if(!strcmp(job.commands[0], "quit"))
		{
			raise(SIGQUIT);
			return 1;
		}
		else if(strcmp(job.commands[0], "jobs"))
		{
			int in = dup(STDIN_FILENO);
			int out = dup(STDOUT_FILENO);
			redirect(job);
			list_jobs();
			dup2(in, STDIN_FILENO);
			close(in);
			dup2(out, STDOUT_FILENO);
			close(out);
			return 1;
		}
		else if(!strcmp(job.commands[0], "bg") || !strcmp(job.commands[0], "fg"))
		{
			switch_job();
			return 1;
		}
		return 0;
	}

	void wait_front_job(pid_t pgid)
	{

	}

	void switch_job()
	{
		
	}
}