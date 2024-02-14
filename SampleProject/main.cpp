// main.cpp

#include "service/LocationService.h"
#include <csignal>
#include <iostream>
#include <unistd.h>

volatile sig_atomic_t signalReceived = 0;

void signalHandler(int signal)
{
    signalReceived = signal;
}

int main()
{
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
