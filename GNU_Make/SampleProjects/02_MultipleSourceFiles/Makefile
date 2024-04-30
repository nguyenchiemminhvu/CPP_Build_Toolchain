CXX := g++
CXXFLAGS = -g -Wall -std=c++11
OBJECTS = main.o simple_algo.o simple_math.o

main : $(OBJECTS)
	$(CXX) $(OBJECTS) -o main

main.o : main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

simple_algo.o : simple_algo.cpp
	$(CXX) -c $(CXXFLAGS) simple_algo.cpp

simple_math.o : simple_math.cpp
	$(CXX) -c $(CXXFLAGS) simple_math.cpp

clean :
	@rm -f main $(OBJECTS)