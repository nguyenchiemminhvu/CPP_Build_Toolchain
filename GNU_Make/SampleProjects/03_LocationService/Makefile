BUILD_DIR := ./build

CXXFLAGS += -I./service -I./core/jsoncpp/include -I./core/nmeaparser/include
LDFLAGS += -L$(BUILD_DIR) -ljsoncpp -lnmeaparser

TARGET = $(BUILD_DIR)/LocationService
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/LocationService.o

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(wildcard $(BUILD_DIR)/*.o) $(LDFLAGS) -o LocationService

jsoncpp :
	$(MAKE) -C core/jsoncpp
	mkdir -p $(BUILD_DIR)
	mv core/jsoncpp/libjsoncpp.so $(BUILD_DIR)/

nmeaparser :
	$(MAKE) -C core/nmeaparser
	mkdir -p $(BUILD_DIR)
	mv core/nmeaparser/libnmeaparser.so $(BUILD_DIR)/

$(BUILD_DIR)/main.o: main.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/LocationService.o: service/LocationService.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

all : $(TARGET)

clean :
	rm -rf $(BUILD_DIR)

.PHONY: all clean jsoncpp nmeaparser