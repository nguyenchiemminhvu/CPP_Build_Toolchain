// LocationService.cpp

#include "LocationService.h"

#include "nmea.h"

LocationService::LocationService()
{
    nmea_zero_INFO(&info);
    nmea_parser_init(&parser);
}

LocationService::~LocationService()
{
    nmea_parser_destroy(&parser);
}

void LocationService::parseNMEAMessage(const std::string& message)
{
    nmea_parse(&parser, message.c_str(), message.length(), &info);
    std::cout << "lat: " << info.lat << " lon: " << info.lon << " alt: " << info.elv << std::endl;
}
