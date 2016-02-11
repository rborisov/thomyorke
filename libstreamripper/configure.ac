dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(libstreamripper, 1.64.7)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CC





LT_INIT


PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.16.1])
PKG_CHECK_MODULES([MAD], [mad >= 0.15])
PKG_CHECK_MODULES([ID3], [id3tag >= 0.15])

dnl -------- Tests for using ogg/vorbis ------
AC_SUBST(VORBIS_CFLAGS)
AC_SUBST(VORBIS_LIBS)
AC_SUBST(OGG_CFLAGS)
AC_SUBST(OGG_LIBS)
sr_have_ogg=no
XIPH_PATH_OGG([
  XIPH_PATH_VORBIS([
    AC_SUBST(OGG_CFLAGS)
    AC_SUBST(OGG_LIBS)
    AC_SUBST(VORBIS_CFLAGS)
    AC_SUBST(VORBIS_LIBS)
    AC_DEFINE(HAVE_OGG_VORBIS,1,[Define to 1 if you have both the ogg and vorbis libraries installed])
    sr_have_ogg=yes
    ],
    AC_DEFINE(HAVE_OGG_VORBIS,0,[Define to 1 if you have both the ogg and vorbis libraries installed]))],
  AC_DEFINE(HAVE_OGG_VORBIS,0,[Define to 1 if you have both the ogg and vorbis libraries installed])
  )


CPPFLAGS="-D__UNIX__"
AC_SUBST(CPPFLAGS)



AC_OUTPUT([
Makefile
src/libstreamripper.pc
src/Makefile
])
