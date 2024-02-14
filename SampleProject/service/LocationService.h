#ifndef LOCATIONSERVICE_H
#define LOCATIONSERVICE_H
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <string>

#include "nmea.h"

class LocationService
{
public:
    void startDaemon();
    pid_t getDaemonPid() const;

private:
    pid_t daemonPid;
    nmeaINFO info;
    nmeaPARSER parser;

    static void handleDaemonSignal(int signal);
    void parseNMEAMessage(const std::string& message);
};

#endif // LOCATIONSERVICE_H
