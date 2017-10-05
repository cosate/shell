#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<errno.h>
#include<vector>
#include"sig.h"
#include"job.h"

extern vector<Job> jobs;

pid_t get_front_job_pid()
{
	for(auto it = jobs.begin(); it != jobs.end(); it++)
	{
		if(it->workmode == FRONTGROUND)
			return it->pgid;
	}
	return 0;
}

signal_handler signal_set_handler(int sig, signal_handler handler)
{
	sigaction act, oldact;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = handler;
	if(sigaction(sig, &act, &oldact) == -1)
	{
		cerr<<"signal handler error"<<endl;
		exit(1);
	}
	return oldact.sa_handler;
}

void sigchld_handler(int sig)
{
	
}

void sigint_handler(int sig)
{
	pid_t currentjob = get_front_job_pid();
	if(currentjob != 0)
		kill(-currentjob.pgid, SIGTINT);
}

void sigquit_handler(int sig)
{
	for(auto it = jobs.begin(); it != jobs.end(); it++)
		kill(-it->pgid, SIGTERM);
	exit(1);
}

void sigtstp_handler(int sig)
{
	pid_t currentjob = get_front_job_pid();
	if(currentjob != 0)
		kill(-currentjob.pgid, SIGTSTP);
}

void signal_mask(int how, int sig)
{

}