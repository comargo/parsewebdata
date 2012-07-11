dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([ParseWebData], [0.0.1], [https://code.google.com/p/parsewebdata/issues/list], [], [https://code.google.com/p/parsewebdata/])
AC_PROG_CC
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 
AC_PROG_CXX

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile
                exampleProgram/Makefile
                ParseWebData/Makefile
                include/Makefile)
AC_OUTPUT