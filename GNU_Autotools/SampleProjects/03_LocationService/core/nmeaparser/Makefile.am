lib_LIBRARIES = libnmeaparser.a
libnmeaparser_a_SOURCES = src/context.cpp \
                          src/generate.cpp \
                          src/generator.cpp \
                          src/gmath.cpp \
                          src/info.cpp \
                          src/parse.cpp \
                          src/parser.cpp \
                          src/sentence.cpp \
                          src/time.cpp \
                          src/tok.cpp
libnmeaparser_a_CPPFLAGS = -I$(top_srcdir)/include \
                           -fPIC
libnmeaparser_a_LDFLAGS = -shared

LocationService_includedir = $(includedir)
LocationService_include_HEADERS = $(top_srcdir)/include/*

lib_LTLIBRARIES = libnmeaparser.la
libnmeaparser_la_SOURCES = $(libnmeaparser_a_SOURCES)
libnmeaparser_la_CPPFLAGS = $(libnmeaparser_a_CPPFLAGS)
libnmeaparser_la_LDFLAGS = $(libnmeaparser_a_LDFLAGS) -version-info 0:0:0

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4