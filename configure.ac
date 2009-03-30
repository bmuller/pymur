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

AC_DEFINE([PYCXX_USING_STD_MAP], [1], [Use std::map])

AX_PYTHON
if test "$ax_python_header" = "no" ; then
   AC_MSG_ERROR([Could not find python header files.])
fi

AX_PYTHON_PACKAGES_DIR
if test "$py_error" = "yes" ; then
   AC_MSG_ERROR([Could not determine location of python's site-packages directory.])
fi

AC_CHECK_HEADER([indri/Index.hpp],,[
   AC_MSG_ERROR([Could not find lemur's header files.])  
])

AX_CXX_CHECK_LIB(lemur, [lemur::retrieval::QnList::QnList () const],,[
   AC_MSG_ERROR([Could not find lemur library.])
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
