lib_LTLIBRARIES = libjsoncpp.la
libjsoncpp_la_SOURCES = $(top_srcdir)/src/json_reader.cpp \
                        $(top_srcdir)/src/json_value.cpp \
                        $(top_srcdir)/src/json_writer.cpp
libjsoncpp_la_CPPFLAGS = -I$(top_srcdir)/include \
                         -fPIC
libjsoncpp_la_LDFLAGS = -version-info 0:0:0 \
                        -shared

ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects