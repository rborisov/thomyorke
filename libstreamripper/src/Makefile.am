## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g \
	 $(GLIB_CFLAGS)

lib_LTLIBRARIES = libstreamripper.la


libstreamripper_la_SOURCES = \
	argv.c \
	cbuf2.c \
	cbuf2.h \
	charmaps.h \
	charset.c \
	charset.h \
	compat.h \
	config.h \
	config.h.in \
	confw32.h \
	debug.c \
	debug.h \
	errors.c \
	errors.h \
	external.c \
	external.h \
	filelib.c \
	filelib.h \
	findsep.c \
	findsep.h \
	findsep2.c \
	http.c \
	http.h \
	iconvert.c \
	list.h \
	mchar.c \
	mchar.h \
	parse.c \
	parse.h \
	prefs.c \
	prefs.h \
	relaylib.c \
	relaylib.h \
	ripaac.c \
	rip_manager.c \
	rip_manager.h \
	ripogg.c \
	ripogg.h \
	ripstream.c \
	ripstream.h \
	socklib.c \
	socklib.h \
	srconfig.h \
	srtypes.h \
	threadlib.c \
	threadlib.h \
	uce_dirent.h \
	utf8.c \
	utf8.h

libstreamripper_la_LDFLAGS = $(GLIB_LIBS)

libstreamripper_la_LIBADD = 

include_HEADERS = \
	libstreamripper.h 

otherincludedir = $(includedir)/sr
otherinclude_HEADERS =  \
	sr/rip_manager.h \
	sr/errors.h \
	sr/prefs.h \
	sr/srtypes.h \
	sr/compat.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libstreamripper.pc

EXTRA_DIST = \
	libstreamripper.pc.in
