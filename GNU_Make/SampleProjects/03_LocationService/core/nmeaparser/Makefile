TARGET = libnmeaparser.so
SRC_DIR = ./src

CXXFLAGS += -fPIC -shared -I./include

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

$(SRC_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

all : $(TARGET)

clean :
	rm -rf $(OBJECTS) $(TARGET)

.PHONY: all clean $(TARGET)