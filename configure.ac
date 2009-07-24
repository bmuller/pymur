AC_INIT([pymur], [0.0], [mullerb@musc.edu])
AC_DEFINE([PACKAGE_URL],["http://projects.dbbe.musc.edu/trac/pymur"],[project url])
AM_CONFIG_HEADER(pymur/config.h)
AM_INIT_AUTOMAKE()

AC_CONFIG_MACRO_DIR([acinclude.d])

AC_PROG_CXX
AC_PROG_CXXCPP
AC_LANG_CPLUSPLUS
AC_CANONICAL_HOST
AC_PROG_INSTALL
AM_PROG_LIBTOOL

AC_HEADER_STDC

AC_PYTHON_DEVEL([>='2.4'])

AC_SUBST([PYTHON])

# This is needed for pycxx
AC_CHECK_HEADER([map], [CPPFLAGS="$CPPFLAGS -DPYCXX_USING_STD_MAP"])

# provide flag --enable-debug
AC_ARG_ENABLE(debug, AC_HELP_STRING([[--enable-debug]], [enable debugging output to stdout]),
[if test "$enableval" = "yes"; then
    DEBUG="yes"
    CPPFLAGS="$CPPFLAGS -DDEBUG"
fi]
)


# option for compiler to be nitpicky about code
nitpick=false
AC_ARG_ENABLE([nitpicking],
 AC_HELP_STRING([--enable-nitpicking],[make compiler somewhat overly fastidious about the code it deals with]),
 [ test "$enableval" = "no" || nitpick=true ]
)
if $nitpick ; then
 CPP_NITPICK="-Wall -Wextra -Wundef -Wshadow -Wunsafe-loop-optimizations -Wconversion -Wmissing-format-attribute"
 CPP_NITPICK="$CPP_NITPICK -Wredundant-decls -ansi -Wmissing-noreturn"
 CPPFLAGS="$CPPFLAGS $CPP_NITPICK"
fi


AC_CHECK_HEADER([indri/Index.hpp],,[
   AC_MSG_ERROR([Could not find lemur's header files.])  
])


AC_MSG_CHECKING([for lemur library])
AC_LINK_IFELSE([#include <QueryNode.hpp>
int main() { lemur::retrieval::QnList l(); return 0; }],[
  AC_MSG_RESULT([yes])
],[
  AC_MSG_FAILURE([Could not find the lemur library.])
])

# due to Lemur's project leaders not including a simple dang pkg-config file, I have to include the following lines:
AC_CHECK_LIB(iberty, mkstemps)
AC_CHECK_FUNCS(mkstemp)
AC_CHECK_FUNCS(mkstemps)
AC_CHECK_LIB(z, deflate)
AC_CHECK_LIB(m, log)
AC_CHECK_LIB(pthread, pthread_create)

P_HAS_ATOMIC_INT=0
P_NEEDS_GNU_CXX_NAMESPACE=0
AC_CHECK_HEADERS([bits/atomicity.h], P_HAS_ATOMIC_INT=1)
AC_CHECK_HEADERS([ext/atomicity.h], P_NEEDS_GNU_CXX_NAMESPACE=1)
if test ${P_HAS_ATOMIC_INT} = 1 ; then
  AC_MSG_CHECKING(if __atomic_add is in __gnu_cxx namespace)
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <bits/atomicity.h>]], [[_Atomic_word val; __gnu_cxx::__atomic_add(&val, 1)]])],[P_NEEDS_GNU_CXX_NAMESPACE=1],[])                                                                                                                                                  
  if test ${P_NEEDS_GNU_CXX_NAMESPACE} = 1 ; then
    AC_MSG_RESULT(yes)
    AC_DEFINE(P_NEEDS_GNU_CXX_NAMESPACE, 1, [define if __atomic_add is in __gnu_cxx namespace])
  else
    AC_MSG_RESULT(no)
    AC_DEFINE(P_NEEDS_GNU_CXX_NAMESPACE, 0, [define if __atomic_add is in __gnu_cxx namespace])
  fi
else
  if test ${P_NEEDS_GNU_CXX_NAMESPACE} = 1 ; then
    AC_DEFINE(P_NEEDS_GNU_CXX_NAMESPACE, 1, [define if __atomic_add is in __gnu_cxx namespace])
  else
    AC_DEFINE(P_NEEDS_GNU_CXX_NAMESPACE, 0, [define if __atomic_add is in __gnu_cxx namespace])
  fi
fi




AC_CONFIG_FILES([
 Makefile
 pymur/Makefile
])
AC_OUTPUT


echo " ***"
echo " *** You are now ready to build pymur"
echo " *** Enter the following commands:"
echo " ***"
echo " *** $> make"
echo " *** $> sudo make install"
echo " ***"
echo " *** Report bugs at http://projects.dbbe.musc.edu/trac/pymur"
echo " *** Thanks for using free (as in speech and beer) software."
echo " ***"
echo
