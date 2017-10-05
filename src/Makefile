shell : shell.o parse.o
	g++ -std=c++11 -o $@ shell.o parse.o
parse.o : job.h
shell.o : job.h
clean :
	rm shell.o parse.o shell