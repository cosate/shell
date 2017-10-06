#include<iostream>
#include<string>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include"job.h"
#include"parse.h"
#include"sig.h"
using namespace std;
using namespace gao;

static vector<Job> jobs;

int main()
{
	signal_set_handler(SIGINT, sigint_handler);
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
		/*if(s == "")
			cout<<"ksdlfk"<<endl;
		cout<<s<<endl;*/
		vec.clear();
		if(parse_jobs(s, vec))
		{
			for(int i = 0; i < vec.size(); i++)
			{
				for(int j = 0; j < vec[i].commands.size(); j++)
				{
					for(int k = 0; k < vec[i].commands[j].argv.size(); k++)
					{
						cout<<vec[i].commands[j].argv[k]<<"-------";
					}
					if(vec[i].commands[j].outfile != NULL)
						cout<<"redirected to "<<vec[i].commands[j].outfile;
					if(vec[i].commands[j].infile != NULL)
						cout<<"redirected to "<<vec[i].commands[j].infile;
					cout<<endl;
				}
				cout<<"new job"<<endl<<endl<<endl;
			}
			cout<<endl;
		}
		else
			cerr<<"wrong cmd"<<endl;
	}
	return 0;
}