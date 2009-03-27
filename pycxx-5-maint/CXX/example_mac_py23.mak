#
#	Build the example on Mac OS X for version 2.3
#
CCC=g++
CCCFLAGS=-c -fPIC -I/System/Library/Frameworks/Python.framework/Versions/2.3/include/python2.3 -I.
LDSHARED=$(CCC) -bundle -g -u _PyMac_Error -F/Library/Frameworks -framework System \
	/Library/Frameworks/Python.framework/Versions/2.3/Python
LDLIBS=
PYTHON=/usr/bin/python

include example_common.mak
