#
#	Build the example on Mac OS X for version 2.4
#
CCC=g++
CCCFLAGS=-c -fPIC -I/Library/Frameworks/Python.framework/Versions/2.4/include/python2.4 -I.
LDSHARED=$(CCC) -bundle -g -u _PyMac_Error -F/Library/Frameworks -framework System \
	/Library/Frameworks/Python.framework/Versions/2.4/Python
LDLIBS=
PYTHON=/Library/Frameworks/Python.framework/Versions/2.4/Resources/Python.app/Contents/MacOS/Python

include example_common.mak
