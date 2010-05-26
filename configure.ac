#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([libstrsafe], [0.0.0], [libstrsafe@jsund.com])
AC_CONFIG_SRCDIR([src/strsafe.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([/usr/share/aclocal])

# Automake settings.
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Checks for programs.
AC_PROG_CC
#AC_PROG_CC_C_0
AC_PROG_LIBTOOL

# Checks for libraries.

# Check for the Check testing framework.
#AM_PATH_CHECK()

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdint.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

# Output files to produce.
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])

# Produce output files.
AC_OUTPUT
