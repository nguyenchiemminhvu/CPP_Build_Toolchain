main : main.o funcs.o
	g++ -o main main.o funcs.o

main.o : main.cpp
	g++ -c main.cpp -lstdc++ -o main.o

funcs.o : funcs.cpp
	g++ -c funcs.cpp -lstdc++ -o funcs.o

clean : 
	rm -rf main main.o
	rm -rf funcs.o
