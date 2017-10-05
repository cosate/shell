#include<iostream>
#include<cstring>
#include<unistd.h>
#include<stdio.h>
#include"parse.h"
using namespace std;

void pass_whitespace(char*& cmd)
{
	while(*cmd != '\0' && *cmd == ' ')
		cmd++;
}

int parse_jobs(string& commandline, vector<Job>& jobs)
{
	char* cmdline = (char*)commandline.c_str();
	while(1)
	{
		if(parse_job(cmdline, jobs))
		{
			if(*cmdline == ';')
			{
				*cmdline = '\0';
				cmdline++;
			}
			else
				break;
		}
		else
		{
			cerr<<"jobs parse wrong"<<endl;
			return 0;
		}
	}
	return 1;
}

int parse_job(char*& cmdline, vector<Job>& jobs)
{
	Job job;
	while(1)
	{
		if(parse_command(cmdline, job))
		{
			if(*cmdline == '|')
			{
				*cmdline = '\0';
				cmdline++;
			}
			else
				break;
		}
		else
		{
			cerr<<"job parse wrong"<<endl;
			return 0;
		}
	}
	if(job.commands.size() != 0)
	{
		cout<<job.commands.back().argv.back()<<endl;
		if(!strcmp(job.commands.back().argv.back(), "&"))
		{
			cout<<"back"<<endl;
			job.commands.back().argv.pop_back();
			job.workmode = BACKGROUND;
		}
		jobs.push_back(job);
	}
	return 1;
}

int parse_command(char*& cmdline, Job& job)
{
	Command cmd;
	char* args;
	while(1)
	{
		pass_whitespace(cmdline);
		args = cmdline;
		while(*cmdline != '\0' && *cmdline != ';' && *cmdline != '|' && *cmdline != ' ' && *cmdline != '>' && *cmdline != '<')
			cmdline++;
		if(*cmdline == ' ')
		{
			*cmdline = '\0';
			cmd.argv.push_back(args);
			cmdline++;
		}
		else if(*cmdline == '>')
		{
			if(cmd.out != 0)
			{
				cerr<<"Has redirected out before "<<cmd.outfile<<"  "<<cmdline<<endl;
				return 0;
			}
			if(args != cmdline)
			{
				*cmdline = '\0';
				cmdline++;
				cmd.argv.push_back(args);
			}
			else
				cmdline++;
			if(*cmdline == '>')
			{
				cmd.out = OUTAPPEND;
				cmdline++;
			}
			else
				cmd.out = OUTREDIRECT;
			pass_whitespace(cmdline);
			cmd.outfile = cmdline;
			while(*cmdline != '\0' && *cmdline != ';' && *cmdline != '|' && *cmdline != ' ' && *cmdline != '>' && *cmdline != '<')
				cmdline++;
			if(cmd.outfile == cmdline)
			{
				cerr<<"no file"<<endl;
				return 0;
			}
			if(*cmdline != '\0')
			{
				if(*cmdline == '>')
				{
					cerr<<"Has redirected out just now "<<cmd.outfile<<"  "<<cmdline<<endl;
					return 0;
				}
				else if(*cmdline == '<')
				{
					if(cmd.infile != NULL)
					{
						cerr<<"Has redirected in before "<<cmd.outfile<<"  "<<cmdline<<endl;
						return 0;
					}
					else
					{
						*cmdline = '\0';
						cmdline++;
						pass_whitespace(cmdline);
						cmd.infile = cmdline;
						while(*cmdline != '\0' && *cmdline != ';' && *cmdline != '|' && *cmdline != ' ' && *cmdline != '>' && *cmdline != '<')
							cmdline++;
						if(cmd.infile == cmdline)
						{
							cerr<<"no file"<<endl;
							return 0;
						}
						if(*cmdline == '>' || *cmdline == '<')
						{
							cerr<<"Has redirected both "<<cmd.outfile<<"  "<<cmdline<<endl;
							return 0;
						}
						else if(*cmdline == ' ')
						{
							*cmdline = '\0';
							cmdline++;
						}
						else
							continue;
					}
				}
				else
				{
					if(*cmdline == ' ')
					{
						*cmdline = '\0';
						cmdline++;
					}
					else
						continue;
				}
			}
		}
		else if(*cmdline == '<')
		{
			if(cmd.infile != NULL)
			{
				cerr<<"Has redirected in before "<<cmd.outfile<<"  "<<cmdline<<endl;
				return 0;
			}
			if(args != cmdline)
			{
				*cmdline = '\0';
				cmdline++;
				cmd.argv.push_back(args);
			}
			else
				cmdline++;
			pass_whitespace(cmdline);
			cmd.infile = cmdline;
			while(*cmdline != '\0' && *cmdline != ';' && *cmdline != '|' && *cmdline != ' ' && *cmdline != '>' && *cmdline != '<')
				cmdline++;
			if(cmd.infile == cmdline)
			{
				cerr<<"no file"<<endl;
				return 0;
			}
			if(*cmdline != '\0')
			{
				if(*cmdline == '<')
				{
					cerr<<"Has redirected in just now "<<cmd.outfile<<"  "<<cmdline<<endl;
					return 0;
				}
				else if(*cmdline == '>')
				{
					if(cmd.outfile != NULL)
					{
						cerr<<"Has redirected out before "<<cmd.outfile<<"  "<<cmdline<<endl;
						return 0;
					}
					else
					{
						*cmdline = '\0';
						cmdline++;
						if(*cmdline == '>')
						{
							cmd.out = OUTAPPEND;
							cmdline++;
						}
						else
							cmd.out = OUTREDIRECT;
						pass_whitespace(cmdline);
						cmd.outfile = cmdline;
						while(*cmdline != '\0' && *cmdline != ';' && *cmdline != '|' && *cmdline != ' ' && *cmdline != '>' && *cmdline != '<')
							cmdline++;
						if(cmd.outfile == cmdline)
						{
							cerr<<"no file"<<endl;
							return 0;
						}
						if(*cmdline == '>' || *cmdline == '<')
						{
							cerr<<"Has redirected both "<<cmd.outfile<<"  "<<cmdline<<endl;
							return 0;
						}
						else if(*cmdline == ' ')
						{
							*cmdline = '\0';
							cmdline++;
						}
						else
							continue;
					}
				}
				else
				{
					if(*cmdline == ' ')
					{
						*cmdline = '\0';
						cmdline++;
					}
					else
						continue;
				}
			}
		}
		else
			break;
	}
	if(*args != '\0' && *args != '|' && *args != ';')
		cmd.argv.push_back(args);
	if(cmd.argv.size() != 0)
		job.commands.push_back(cmd);
	return 1;
}