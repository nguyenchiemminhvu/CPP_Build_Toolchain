main : main.o
	g++ -o main main.o

main.o : main.cpp defs.h
	g++ -c main.cpp -lstdc++ -o main.o

clean : 
	rm main main.o
