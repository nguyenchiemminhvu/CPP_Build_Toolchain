bin_PROGRAMS = LocationService
LocationService_SOURCES = service/LocationService.cpp \
                          main.cpp
LocationService_LDFLAGS = -ljsoncpp \
                          -lnmeaparser \
                          -pthread

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4