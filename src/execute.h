#ifndef _EXECUTE_H
#define _EXECUTE_H

#include<sys/types.h>
#include<unistd.h>
#include"job.h"

namespace gao
{
	void just_do_it(char*);
	pid_t excute(Job&);
	bool build_in(Command*);
	void shift_n(char**, int);
	int redirect(Command* );
	pid_t fork_pipes(Job&);
	pid_t spawn_proc(int, int, Command*, pid_t);
	void do_bgfg(Command*);
	void wait_fg(pid_t);
}
#endif