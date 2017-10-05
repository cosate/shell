#ifndef _PARSE_H
#define _PARSE_H

#include<string>
#include"job.h"

void pass_whitespace(char*&);
int parse_jobs(string&, vector<Job>&);
int parse_job(char*&, vector<Job>&);
int parse_command(char*&, Job&);
int execute(Job&);

#endif