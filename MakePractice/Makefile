OBJECTS = main.o \
	  funcs.o

CPP_FILES = main.cpp \
	    funcs.cpp

main : $(OBJECTS)
	g++ -o main $(OBJECTS)

main.o : main.cpp
	g++ -c main.cpp -lstdc++ -o main.o

funcs.o : funcs.cpp
	g++ -c funcs.cpp -lstdc++ -o funcs.o

clean : 
	rm -rf main
	rm -rf $(OBJECTS)
