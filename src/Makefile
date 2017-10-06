shell : shell.o parse.o job.o sig.o
	g++ -std=c++11 -o $@ shell.o parse.o sig.o
shell.o :
	g++ -std=c++11 -c shell.cpp parse.h job.h
parse.o :
	g++ -std=c++11 -c parse.cpp parse.h job.h
job.o :
	g++ -std=c++11 -c job.cpp job.h
sig.o:
	g++ -std=c++11 -c sig.cpp sig.h
clean :
	rm shell.o parse.o job.o shell