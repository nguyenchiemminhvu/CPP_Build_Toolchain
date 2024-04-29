main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c -Wall -g -std=c++11 main.cpp

dump:
	@echo "Object files in the current directory:"; ls -1 *.o

clean:
	@rm -rf *.o main