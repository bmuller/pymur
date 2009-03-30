pkglib_LTLIBRARIES = libpymur.la
libpymur_la_SOURCES = CXX/cxxsupport.cxx CXX/cxx_extensions.cxx CXX/cxxextensions.c CXX/IndirectPythonInterface.cxx \
		      index.cpp pymur.cpp
noinst_DATA = pymur.so

INCLUDES = -I${PYTHON_INCLUDE_DIR}
AM_LDFLAGS = -l${PYTHON_LIB} -lz -lpthread -lm -llemur
AM_CPPFLAGS = -DHAVE_EXT_ATOMICITY_H=1 -DP_NEEDS_GNU_CXX_NAMESPACE=1

install-exec-local:
	cp pymur.so ${PYTHON_PACKAGES_DIR}

uninstall-local:
	rm -f ${PYTHON_PACKAGES_DIR}/pymur.so

pymur.so: libpymur.la
	cp .libs/libpymur.so.0.0.0 pymur.so