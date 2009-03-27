#
#	Build the example on Mac OS X for fink version 2.4
#
CCC=MACOSX_DEPLOYMENT_TARGET=10.4 g++ -c
CCCFLAGS=-g -fPIC -Wno-long-double -I/sw/include/python2.4 -I.
LDSHARED=MACOSX_DEPLOYMENT_TARGET=10.4 g++ -g -L/sw/lib -bundle -undefined dynamic_lookup
LDLIBS=-flat_namespace
PYTHON=/sw/bin/python2.4

include example_common.mak
