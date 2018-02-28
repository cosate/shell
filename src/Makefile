shell : shell.o execute.o job.o sig.o err.o
	g++ -std=c++11 -o $@ shell.o execute.o job.o sig.o err.o
shell.o :
	g++ -std=c++11 -c shell.cpp
execute.o :
	g++ -std=c++11 -c execute.cpp
job.o :
	g++ -std=c++11 -c job.cpp
sig.o :
	g++ -std=c++11 -c sig.cpp
err.o :
	g++ -std=c++11 -c err.cpp
clean :
	rm -f *.o *.h.gch shell