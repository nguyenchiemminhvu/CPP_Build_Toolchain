#ifndef LOCATIONSERVICE_H
#define LOCATIONSERVICE_H
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <cstring>
#include <iostream>
#include <string>

#include "nmea.h"

class LocationService
{
public:
    LocationService();
    ~LocationService();
    void parseNMEAMessage(const std::string& message);

private:
    pid_t daemonPid;
    nmeaINFO info;
    nmeaPARSER parser;
};

#endif // LOCATIONSERVICE_H
