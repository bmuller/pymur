#
#	BUild the example on Linux for version 2.2
#
CCC=g++ -c
CCCFLAGS=-fPIC -I/usr/include/python2.4 -I.
LDSHARED=g++ -shared
LDLIBS=
PYTHON=python2.4

include example_common.mak
