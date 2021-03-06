#                                               -*- Autoconf -*-
AC_PREREQ([2.64])

AC_INIT([duplo],
        [m4_esyscmd_s([./get-version])],
        [david.eisner@oriel.oxon.org])
AC_CONFIG_SRCDIR([src/log.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror tar-ustar])
AM_MAINTAINER_MODE
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES(yes)])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR

# Configure libtool
LT_INIT

#######################
### Checks

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_EGREP

# Check some compiler flags
AX_CFLAGS_GCC_OPTION([-fdiagnostics-show-option])
AX_CFLAGS_GCC_OPTION([-pipe])
AX_CFLAGS_GCC_OPTION([-Wall])
AX_CFLAGS_GCC_OPTION([-W])
AX_CFLAGS_GCC_OPTION([-Wextra])
AX_CFLAGS_GCC_OPTION([-Wformat])
AX_CFLAGS_GCC_OPTION([-Wformat-security])
AX_CFLAGS_GCC_OPTION([-Wfatal-errors])
AX_CFLAGS_GCC_OPTION([-Wcast-align])
AX_CFLAGS_GCC_OPTION([-Winline])
AX_CFLAGS_GCC_OPTION([-D_FORTIFY_SOURCE=2])
AX_CFLAGS_GCC_OPTION([-Wno-unused-parameter])
AX_CFLAGS_GCC_OPTION([-Wno-missing-field-initializers])
AX_LDFLAGS_OPTION([-Wl,-z,relro])
AX_LDFLAGS_OPTION([-Wl,-z,now])

dnl Enable _GNU_SOURCE and the like
AX_CFLAGS_GCC_OPTION([-D_GNU_SOURCE])    dnl GNU systems (asprintf, ...)
case $host_os in
   solaris*)
     AX_CFLAGS_GCC_OPTION([-D__EXTENSIONS__]) dnl (CMSG_*)
     AX_CFLAGS_GCC_OPTION([-D_XPG4_2])        dnl (CMSG_*)
     ;;
   hpux*)
     AX_CFLAGS_GCC_OPTION([-D_XOPEN_SOURCE=500])      dnl HP-UX
     AX_CFLAGS_GCC_OPTION([-D_XOPEN_SOURCE_EXTENDED]) dnl HP-UX
     ;;
esac

AC_CACHE_SAVE

AC_CHECK_LIB([pthread], [pthread_mutex_init])

AC_CHECK_HEADERS([ linux/input.h ])
AC_CHECK_HEADERS([ linux/uinput.h ])
AC_CHECK_HEADERS([ linux/i2c-dev.h ])

PKG_CHECK_MODULES([LIRC], [lirc >= 0.9.2])

AC_CACHE_SAVE

AC_OUTPUT

cat <<EOF

------------------ Summary ------------------
 $PACKAGE_NAME version $PACKAGE_VERSION
  Prefix.........: $prefix
  C Compiler.....: $CC $CFLAGS $CPPFLAGS
  Linker.........: $LD $LDFLAGS $LIBS
---------------------------------------------

Check the above options and compile with:
 ${MAKE-make}

EOF
