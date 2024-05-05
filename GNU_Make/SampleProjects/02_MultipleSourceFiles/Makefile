CXXFLAGS = -g -Wall -std=c++11 -O2
OBJECTS = main.o simple_algo.o simple_math.o

main: $(OBJECTS)
	$(CXX) $^ -o $@

clean:
	@rm -f main $(OBJECTS)

.PHONY: clean