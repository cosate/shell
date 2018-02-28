#include<iostream>
#include<string>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include"job.h"
#include"sig.h"
#include"err.h"
#include"execute.h"
using namespace std;
using namespace gao;

vector<Job> jobs;

static int get_cmd(char* cmd, int max)
{
	char c;
	int nread = 0;
	while((c = getchar()) != EOF)
	{
		if(c == '\n' || c == ';')
			break;
		nread++;
		if(nread > max)
		{
			err_msg("get_cmd");
			return 0;
		}
		*cmd++ = c;
	}
	*cmd = '\0';

	if(c == EOF && nread == 0)
		return -1;
	if(nread == 0)
		return 0;
	return 1;
}

int main(int argc, char* argv[])
{
	signal_set_handler(SIGINT, sigint_handler);
	signal_set_handler(SIGCHLD, sigchld_handler);
	signal_set_handler(SIGQUIT, sigquit_handler);
	signal_set_handler(SIGTSTP, sigtstp_handler);

	char host[10];
	gethostname(host, 10);

	char cmd[MAXCMDLINELENGTH];
	
	while(1)
	{
		cout<<host<<">>: "<<flush;
		
		if(s == "quit")
			break;

		switch(get_cmd(cmd, MAXCMDLINELENGTH))
		{
			case -1:
			{
				raise(SIGQUIT);
				break;
			}
			case 0:
				continue;
			case 1:
			{
				just_do_it(cmd);
				cout<<flush;
			}
			default:
			{
				err_msg("unkown");
				break;
			}
		}
	}
	exit(0);
}