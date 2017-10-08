#include<iostream>
#include<string>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include"job.h"
#include"parse.h"
#include"sig.h"
//#include"execute.h"
using namespace std;
using namespace gao;

vector<Job> jobs;

int main()
{
	signal_set_handler(SIGINT, sigint_handler);
	signal_set_handler(SIGCHLD, sigchld_handler);
	signal_set_handler(SIGQUIT, sigquit_handler);
	signal_set_handler(SIGTSTP, sigtstp_handler);

	char host[10];
	gethostname(host, 10);
	string s;
	vector<Job> vec;
	while(1)
	{
		cout<<host<<">>: "<<flush;
		getline(cin, s);
		if(s == "quit")
			break;
		vec.clear();
		if(parse_jobs(s, vec))
		{
			for(int i = 0; i < vec.size(); i++)
			{
				print_job(vec[i]);
				cout<<"new job"<<endl<<endl<<endl;
			}
			cout<<endl;
		}
		else
			cerr<<"wrong cmd"<<endl;
	}
	return 0;
}