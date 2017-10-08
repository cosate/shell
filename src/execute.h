#ifndef _EXECUTE_H
#define _EXECUTE_H

#include<sys/types.h>
#include<unistd.h>
#include"job.h"

namespace gao
{
	void execute(Job&);
	pid_t execute_single_command(Job&);
	pid_t execute_pipe(Job&);
	int build_in(Job&);
	void wait_front_job(pid_t);
	void switch_job();
}
#endif