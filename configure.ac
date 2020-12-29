# Process this file with autoconf to produce configure.

# Copyright (C) 2018-2021 Jérémy Oden <jerem.oden@gmail.com>
# Copyright (C) 2018-2021 Nicolas Boulenguez <nicolas@debian.org>

# https://www.gnu.org/software/autoconf/manual/autoconf.html
AC_INIT([libeXaDrums],
        [0.6.0],
        [Jérémy Oden <jerem.oden@gmail.com>],
        [],
        [https://exadrums.com])
AC_CONFIG_SRCDIR([Api/eXaDrums.cpp])
AC_PROG_CXX
AC_CONFIG_MACRO_DIRS([m4])

# https://www.gnu.org/software/automake/manual/automake.html
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_PROG_AR

# https://www.gnu.org/software/libtool/manual/libtool.html
LT_INIT

# https://autotools.io/pkgconfig/pkg_check_modules.html
PKG_CHECK_MODULES([alsa], [alsa])
PKG_CHECK_MODULES([tinyxml2], [tinyxml2])
PKG_CHECK_MODULES([minizip], [minizip])

AC_CONFIG_FILES([
  Makefile
  Api/Version.h
])
AC_OUTPUT
