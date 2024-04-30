main : main.o simple_algo.o simple_math.o
	g++ main.o \
		simple_algo.o \
		simple_math.o \
		-o main

main.o : main.cpp
	g++ \
		-c \
		-g \
		-Wall \
		-std=c++11 \
		main.cpp

simple_algo.o : simple_algo.cpp
	g++ \
		-c \
		-g \
		-Wall \
		-std=c++11 \
		simple_algo.cpp

simple_math.o : simple_math.cpp
	g++ \
		-c \
		-g \
		-Wall \
		-std=c++11 \
		simple_math.cpp

clean :
	@rm -f \
		simple_math.o \
		simple_algo.o \
		main.o \
		main