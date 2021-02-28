# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11

# All Targets
all: cTrace

cTrace: bin/main.o bin/agent.o bin/session.o bin/graph.o bin/tree.o
	@echo 'Building target: main'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/cTrace bin/main.o bin/agent.o bin/graph.o bin/tree.o bin/session.o
	@echo 'Finished building target: main'
	@echo ' '

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

bin/agent.o: src/Agent.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/agent.o src/Agent.cpp
	
bin/session.o: src/Session.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/session.o src/Session.cpp
	
bin/graph.o: src/Graph.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/graph.o src/Graph.cpp
	
bin/tree.o: src/Tree.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/tree.o src/Tree.cpp
	
#Clean the build directory
clean: 
	rm -f bin/*
