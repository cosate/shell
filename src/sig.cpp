#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<errno.h>
#include<vector>
#include"sig.h"
#include"job.h"

namespace gao
{
	extern vector<Job> jobs;
	
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
		int saved_errno = errno;
		int status;
		pid_t pid;
		while((pid = waitpid(-1, &status, WNOHANG)) > 0)
		{
			if(WIFSIGNALED(status))
			{
				cerr<<"Job "<<pid2jobid(pid)<<" terminated by signal"<<strsignal(WTERMSIG(status))<<endl;
				kill(-pid2jobid(pid), SIGINT);
				jobs.erase(jobs.begin() + pid2index(pid));
			}
			else if(WIFSTOPPED(status))
			{
				cout<<"Job "<<pid2jobid(pid)<<" stopped by signal"<<strsignal(WSTOPSIG(status))<<endl;
				*(jobs.begin() + pid2index(pid)).state = STOPPED;
			}
		}

		if(pid == -1 && errno == ECHILD)
			cerr<<"waitpid error"<<endl;
		errno = saved_errno;
	}

	void sigint_handler(int sig)
	{
		pid_t currentjob = get_front_job();
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
		int currentjob = get_front_job();
		if(currentjob != -1)
			kill(-jobs[currentjob].pgid, SIGTSTP);
	}

	void signal_mask(int how, int sig)
	{
		sigset_t mask;
		sigemptyset(&mask);
		sigaddset(&mask, sig);
		sigprocmask(how, &mask, NULL);
	}
}