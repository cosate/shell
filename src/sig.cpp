#include<iostream>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<cstring>
#include<errno.h>
#include<unistd.h>
#include<vector>
#include"sig.h"
#include"job.h"
using namespace std;

extern vector<gao::Job> jobs;

namespace gao
{
	signal_handler signal_set_handler(int sig, signal_handler handler)
	{
		struct sigaction act, oldact;
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
			pid_t pgid = getpgid(pid);
			if(WIFSIGNALED(status))
			{
				cerr<<"Job "<<pgid2jobid(pid)<<" terminated by signal"<<strsignal(WTERMSIG(status))<<endl;
				kill(-pgid, SIGINT);
				if(pgid2index(pgid) != -1)
					jobs.erase(jobs.begin() + pgid2index(pgid));
			}
			else if(WIFSTOPPED(status))
			{
				cout<<"Job "<<pgid2jobid(pgid)<<" stopped by signal"<<strsignal(WSTOPSIG(status))<<endl;
				(*(jobs.begin() + pgid2index(pgid))).state = JobState::STOPPED;
			}
		}

		if(pid == -1 && errno == ECHILD)
		{
			cerr<<"waitpid error"<<endl;
			exit(1);
		}
		errno = saved_errno;
	}

	void sigint_handler(int sig)
	{
		int currentjob = get_front_job();
		if(currentjob != -1)
			kill(-(jobs[currentjob].pgid), SIGINT);
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