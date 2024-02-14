// LocationService.cpp

#include "LocationService.h"

#include "nmea.h"

void LocationService::startDaemon()
{
    // Fork the process
    pid_t pid = fork();

    if (pid < 0)
    {
        // Fork failed
        std::cerr << "Failed to fork the process." << std::endl;
        exit(1);
    }

    if (pid > 0)
    {
        // Parent process
        daemonPid = pid; // Save the daemon process ID
        return; // Return to the main process
    }

    // Create a new session
    if (setsid() < 0)
    {
        std::cerr << "Failed to create a new session." << std::endl;
        exit(1);
    }

    // Change the working directory to root
    if (chdir("/") < 0)
    {
        std::cerr << "Failed to change the working directory to /." << std::endl;
        exit(1);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Set up signal handling for the daemon
    struct sigaction action;
    action.sa_handler = &LocationService::handleDaemonSignal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGTERM, &action, NULL);

    // Set up parser
    nmea_zero_INFO(&info);
    nmea_parser_init(&parser);

    // Now the process is daemonized
    // Read from stdin and parse NMEA messages
    std::string input;
    while (std::getline(std::cin, input))
    {
        parseNMEAMessage(input);
    }
}

void LocationService::handleDaemonSignal(int signal)
{
    // Handle the SIGTERM signal or other signals if needed
    // Perform cleanup tasks if necessary
    exit(0); // Terminate the daemon process
}

void LocationService::parseNMEAMessage(const std::string& message)
{
    nmea_parse(&parser, message.c_str(), message.length(), &info);
}

pid_t LocationService::getDaemonPid() const
{
    return daemonPid;
}
