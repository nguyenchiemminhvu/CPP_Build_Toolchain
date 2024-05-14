// main.cpp

#include "json/json.h"
#include "service/LocationService.h"
#include <csignal>
#include <iostream>
#include <string>
#include <memory>
#include <unistd.h>

volatile sig_atomic_t signalReceived = 0;

void signalHandler(int signal)
{
    signalReceived = signal;
}

int main()
{
    const std::string rawJsonConfig = R"({"version": "1.0.0", "service_name": "Location service"})";
    const int rawJsonConfigLength = static_cast<int>(rawJsonConfig.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJsonConfig.c_str(), rawJsonConfig.c_str() + rawJsonConfigLength, &root, &err))
    {
        std::cout << "Failed to read the configuration" << std::endl;
        return -1;
    }

    const std::string service_name = root["service_name"].asString();
    const std::string version = root["version"].asString();
    std::cout << service_name << std::endl;
    std::cout << version << std::endl;
    
    LocationService service;

    // Set up signal handling
    struct sigaction action;
    action.sa_handler = signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    // Wait for the signal to exit
    while (signalReceived == 0)
    {
        // Now the process is daemonized
        // Read from stdin and parse NMEA messages
        std::string input;
        while (std::getline(std::cin, input))
        {
            std::cout << "Receive user input: " << input << std::endl;
            service.parseNMEAMessage(input);
        }
    }

    std::cout << "Received SIGINT. Cleaning up and exiting." << std::endl;

    return 0;
}
