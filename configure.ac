dnl Process this file with autoconf to produce a configure script.
dnl This config.in requires autoconf 2.5 or greater.

AC_PREREQ([2.68])
AC_INIT([build],[0.0.1])

AC_PROG_CC
AC_SUBST(WFLAGS)
AC_SUBST(CXXWFLAGS)

AC_MSG_CHECKING(which build rules to use)
AC_SUBST(BUILDRULES)
AC_ARG_WITH(buildrules,
   AS_HELP_STRING([--with-buildrules=rules],
		  [which build rules to use; see README.md]),
   [BUILDRULES=$withval],
   [BUILDRULES=libtool])
AC_MSG_RESULT($BUILDRULES)

qpdf_USE_EXTRA_WARNINGS=0
if test "$BUILDRULES" = "msvc"; then
   dnl /w14996 makes warning 4996 a level 1 warning.  This warning
   dnl reports on functions that Microsoft considers unsafe or
   dnl deprecated.  Removing these warnings helps people who want to
   dnl write applications based on qpdf that can be Windows 8
   dnl certified.
   try_flags="-w14996"
else
   try_flags="-Wall"
fi
AC_MSG_CHECKING(for whether $CC supports $try_flags)
oCFLAGS=$CFLAGS
CFLAGS="$CFLAGS $try_flags"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[int a = 1; int b = a; a = b;]])],
                  [qpdf_USE_EXTRA_WARNINGS=1],[qpdf_USE_EXTRA_WARNINGS=0])
CFLAGS=$oCFLAGS
if test "$qpdf_USE_EXTRA_WARNINGS" = "1"; then
   AC_MSG_RESULT(yes)
   WFLAGS="$try_flags"
else
   AC_MSG_RESULT(no)
fi

if test "$BUILDRULES" = "msvc"; then
   try_flags="-W3"
else
   try_flags="-Wconversion -Wsign-conversion"
fi
oCFLAGS=$CFLAGS
CFLAGS="$CFLAGS $try_flags"
AC_MSG_CHECKING(for whether to use $try_flags)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[int a = 1; int b = a; a = b;]])],
                  [qpdf_INT_WARNINGS=1],[qpdf_INT_WARNINGS=0])
if test "$qpdf_INT_WARNINGS" = "1"; then
   AC_MSG_RESULT(yes)
   CXXFLAGS="$CXXFLAGS $try_flags"
else
   AC_MSG_RESULT(no)
   CFLAGS=$oCFLAGS
fi

AC_MSG_WARN(CFLAGS = $CFLAGS)
