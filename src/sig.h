#ifndef _SIG_H
#define _SIG_H

namespace gao
{
	typedef void (*signal_handler)(int);

	signal_handler signal_set_handler(int, signal_handler);

	void sigint_handler(int);
	void sigchld_handler(int);
	void sigtstp_handler(int);
	void sigquit_handler(int);

	void signal_mask(int, int);
}

#endif