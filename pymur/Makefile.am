pkglib_LTLIBRARIES = libpymur.la
libpymur_la_SOURCES = CXX/cxxsupport.cxx CXX/cxx_extensions.cxx CXX/cxxextensions.c CXX/IndirectPythonInterface.cxx \
		      argchecker.cpp index.cpp index_environment.cpp utils.cpp pymur.cpp query_environment.cpp \
		      scored_extent_result.cpp parsed_document.cpp field_info.cpp
noinst_DATA = pymur.so

INCLUDES = -I${PYTHON_INCLUDE_DIR}
AM_LDFLAGS = -llemur ${PYTHON_LDFLAGS} ${PYTHON_EXTRA_LIBS} ${PYTHON_EXTRA_LDFLAGS}
AM_CPPFLAGS = -O2 -g -fPIC ${PYTHON_CPPFLAGS} 

install-exec-local:
	cp pymur.so ${PYTHON_SITE_PKG}

uninstall-local:
	rm -f ${PYTHON_SITE_PKG}/pymur.so

pymur.so: libpymur.la
	cp .libs/libpymur.so.0.0.0 pymur.so