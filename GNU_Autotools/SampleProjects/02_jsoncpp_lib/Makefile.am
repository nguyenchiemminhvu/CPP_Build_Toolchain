lib_LIBRARIES = libjsoncpp.a
libjsoncpp_a_SOURCES = src/json_reader.cpp \
                       src/json_value.cpp \
                       src/json_writer.cpp
libjsoncpp_a_CPPFLAGS = -I$(top_srcdir)/include \
                        -fPIC
libjsoncpp_a_LDFLAGS = -shared

lib_LTLIBRARIES = libjsoncpp.la
libjsoncpp_la_SOURCES = $(libjsoncpp_a_SOURCES)
libjsoncpp_la_CPPFLAGS = $(libjsoncpp_a_CPPFLAGS)
libjsoncpp_la_LDFLAGS = $(libjsoncpp_a_LDFLAGS) -version-info 0:0:0

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4