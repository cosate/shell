#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<errno.h>
#include"sig.h"

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

}

void sigquit_handler(int sig)
{

}

void sigtstp_handler(int sig)
{
	
}