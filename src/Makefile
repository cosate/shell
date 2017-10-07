shell : shell.o parse.o job.o sig.o
	g++ -std=c++11 -o $@ shell.o parse.o job.o sig.o
shell.o :
	g++ -std=c++11 -c shell.cpp
parse.o :
	g++ -std=c++11 -c parse.cpp
job.o :
	g++ -std=c++11 -c job.cpp
sig.o :
	g++ -std=c++11 -c sig.cpp
clean :
	rm -f *.o *.h.gch shell