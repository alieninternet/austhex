dnl $Id$

dnl Initialise the autoconf/automake things
AC_INIT([mod_austhex], [0.1.cvs], [dev@austnet.org])
AM_INIT_AUTOMAKE([1.6.1 foreign no-installinfo no-installman nostdinc subdir-objects])
AC_PREREQ(2.57)
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(src/autoconf.h)
AC_REVISION([$Revision$])

dnl Check for required software
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_CHECK_PROG(AUTOGEN, autogen, autogen)

dnl Configure libtool..
AC_DISABLE_FAST_INSTALL
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL

dnl Save the cache file prior to checking for stuff that make cause us to break
AC_CACHE_SAVE

dnl Change to C++ mode for tests..
AC_LANG_CPLUSPLUS

dnl Check for kine..
AC_CHECK_LIB(kineircd, main, [], [
  AC_MSG_ERROR([Missing KineIRCd (please see http://kineircd.sourceforge.net/)])
 ])
AC_CHECK_LIB(kineircd_clbp, main, [], [
  AC_MSG_ERROR([Incomplete KineIRCd installation (please see http://kineircd.sourceforge.net/)])
 ])
AC_CHECK_HEADER([kineircd/version.h], [], [
  AC_MSG_ERROR([Incomplete KineIRCd installation (please see http://kineircd.sourceforge.net/)])
 ])

dnl Maintainer mode needed?
AM_MAINTAINER_MODE

dnl Output the files..
AC_OUTPUT([Makefile])
