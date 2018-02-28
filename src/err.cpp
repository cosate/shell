#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include "err.h"

namespace gao
{
    /* 辅助函数， 输出错误消息 */
    static void output_msg(const char *format, va_list arg, int err)
    {
    #define BUF_SIZE 500
        char buf[BUF_SIZE], user_msg[BUF_SIZE], err_msg[BUF_SIZE];

        vsnprintf(user_msg, BUF_SIZE, format, arg);
        if (err)
            snprintf(err_msg, BUF_SIZE, "[%s]", strerror(err));
        else
            snprintf(err_msg, BUF_SIZE, ":");
        snprintf(buf, BUF_SIZE, "ERROR%s %s\n", err_msg, user_msg);

        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }
 
    /* 仅输出错误消息不退出 */
    void err_msg(const char *format, ...)
    {
        va_list arg;

        va_start(arg, format);
        output_msg(format, arg, 0);
        va_end(arg);
    }

    /* 输出错误消息并退出 */
    void err_exit(const char *format, ...)
    {
        va_list arg;

        va_start(arg, format);
        output_msg(format, arg, 0);
        va_end(arg);

        exit(1);
    }

    /* 输出错误消息和errno并退出 */
    void err_sys(const char *format, ...)
    {
        va_list arg;

        va_start(arg, format);
        output_msg(format, arg, errno);
        va_end(arg);

        exit(1);
    }

    /* 输出usage并退出 */
    void usage_err(const char *format, ...)
    {
        va_list arg;

        fflush(stdout);
        fprintf(stderr, "Usage: ");
        
        va_start(arg, format);
        vfprintf(stderr, format, arg);
        fprintf(stderr, "\n");
        va_end(arg);

        fflush(stderr);
        exit(1);
    }
}