#
#	BUild the example on Linux for version 2.3
#
CCC=g++ -c
CCCFLAGS=-fPIC -I/usr/include/python2.3 -I.
LDSHARED=g++ -shared
LDLIBS=
PYTHON=python2.3

include example_common.mak
