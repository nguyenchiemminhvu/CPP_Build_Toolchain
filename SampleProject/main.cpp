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
    service.startDaemon();

    // Set up signal handling
    struct sigaction action;
    action.sa_handler = signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    // Wait for the signal to exit
    while (signalReceived == 0)
    {
        // You can perform other tasks here while waiting
    }

    std::cout << "Received SIGINT. Cleaning up and exiting." << std::endl;

    // Perform cleanup tasks if needed

    // Terminate the daemon process
    kill(service.getDaemonPid(), SIGTERM);

    return 0;
}
