AC_INIT([pymer], [0.0], [mullerb@musc.edu])
AC_DEFINE([PACKAGE_URL],["http://projects.dbbe.musc.edu/trac/pymer"],[project url])
AM_CONFIG_HEADER(src/config.h)
AM_INIT_AUTOMAKE()

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AC_PROG_CXXCPP
AC_LANG_CPLUSPLUS
AC_CANONICAL_HOST
AC_PROG_INSTALL
AM_PROG_LIBTOOL

AC_HEADER_STDC

AC_PYTHON_DEVEL([>='2.4'])

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


AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT


echo " ***"
echo " *** You are now ready to build pymer"
echo " *** Enter the following commands:"
echo " ***"
echo " *** $> make"
echo " *** $> sudo make install"
echo " ***"
echo " *** Report bugs at http://projects.dbbe.musc.edu/trac/pymer"
echo " *** Thanks for using free (as in speech and beer) software."
echo " ***"
echo
