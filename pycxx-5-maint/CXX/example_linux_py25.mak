#
#	BUild the example on Linux for version 2.5
#
CCC=g++ -c
CCCFLAGS=-fPIC -I/usr/include/python2.5 -I.
LDSHARED=g++ -shared
LDLIBS=
PYTHON=python2.5

include example_common.mak
