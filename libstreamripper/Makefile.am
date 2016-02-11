## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

libstreamripperdocdir = ${prefix}/doc/libstreamripper
libstreamripperdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(libstreamripperdoc_DATA)

#CLEANFILES = $(shell find . -name "*~")



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(libstreamripperdocdir)
