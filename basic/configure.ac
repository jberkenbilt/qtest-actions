dnl Process this file with autoconf to produce a configure script.
dnl This config.in requires autoconf 2.5 or greater.

AC_PREREQ([2.68])
AC_INIT([build],[0.0.1])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([autoconf.mk])

AC_PROG_CC
AC_PROG_CXX
AC_HEADER_STDC
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

dnl CUSTOM

POS_FMT=""
for fmt in "%z" "%lld" "%I64d" "I64lld"; do
  if test "$POS_FMT" = ""; then
    AC_MSG_CHECKING(for whether to use $fmt)
    AC_RUN_IFELSE([AC_LANG_PROGRAM(
     [[
        #include <stdio.h>
        #include <string.h>
     ]],
     [[
        long long int a = 123456789012345ll;
        char s[30];
        sprintf(s, "]$fmt[", a);
        return (strcmp(s, "123456789012345") == 0) ? 0 : 1
     ]]
     )],
     [POS_FMT=$fmt],[],[POS_FMT="%lld"])
    if test "$POS_FMT" != ""; then
       AC_MSG_RESULT(yes)
    else
       AC_MSG_RESULT(no)
    fi
  fi
done
if test "$POS_FMT" != ""; then
  AC_DEFINE_UNQUOTED([POS_FMT], ["$POS_FMT"], [printf format for long long])
fi
if test "$Z" != ""; then
  AC_DEFINE_UNQUOTED([Z], [1], [not used])
fi

AC_SUBST(WINDOWS_WMAIN_XLINK_FLAGS)
AC_SUBST(WINDOWS_MAIN_XLINK_FLAGS)
if test "$BUILDRULES" = "msvc"; then
  WINDOWS_WMAIN_XLINK_FLAGS="-link wsetargv.obj"
  WINDOWS_MAIN_XLINK_FLAGS="-link setargv.obj"
fi

AC_MSG_WARN(CFLAGS = $CFLAGS)
AC_MSG_WARN(POS_FMT = $POS_FMT)

dnl END CUSTOM

AC_OUTPUT

cat config.h
