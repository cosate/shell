# shell

* 支持信号传递: ctrl-c, ctrl-z, ctrl-\
* 支持任务控制: bg, fg
* 支持shell内置命令
* 支持重定向和管道
* 支持进程回收和任务清理
* bug: 本程序shell中执行的程序如果需要从终端读入，会出现STGTTIN信号错误。 因为本shell拥有控制终端，和Linux shell属于同一进程组的才可以读终端, 可能需要伪终端。
