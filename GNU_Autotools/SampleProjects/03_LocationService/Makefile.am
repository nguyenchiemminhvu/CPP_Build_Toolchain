bin_PROGRAMS = LocationService
LocationService_SOURCES = service/LocationService.cpp \
                          main.cpp
LocationService_CXXFLAGS = -I$(top_srcdir)/core/jsoncpp/include \
                           -I$(top_srcdir)/core/nmeaparser/include \
                           -Wall
LocationService_LDFLAGS = -ljsoncpp \
                          -lnmeaparser \
                          -lpthread

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = core/jsoncpp core/nmeaparser
