shell : job.o parse.o shell.o
	g++ -std=c++11 -o $@ job.o parse.o shell.o
job.o : job.cpp job.h
	g++ -std=c++11 -o job.o job.cpp job.h
parse.o : parse.cpp parse.h job.h
	g++ -std=c++11 -o parse.o parse.cpp parse.h job.h
shell.o : shell.cpp parse.h job.h
	g++ -std=c++11 -o shell.o shell.cpp parse.h job.h
clean :
	rm shell.o parse.o shell