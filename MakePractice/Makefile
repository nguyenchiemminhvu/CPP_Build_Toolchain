OBJECTS = main.o \
	  funcs.o

CPP_FILES = main.cpp \
	    funcs.cpp

main : $(OBJECTS)
	g++ -o main $(OBJECTS)

$(OBJECTS) : $(CPP_FILES)

clean : 
	rm -rf main
	rm -rf $(OBJECTS)
