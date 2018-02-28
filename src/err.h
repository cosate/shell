#ifndef _ERR_H
#define _ERR_H

namespace gao
{
	void err_msg(const char *, ...);

	void err_exit(const char *, ...);

	void err_sys(const char *, ...);

	void usage_err(const char *, ...);
}

#endif