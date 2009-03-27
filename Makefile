CCFLAGS=-Wall -fPIC -fexceptions -pthread -fno-strict-aliasing -g -O2 -DNDEBUG -DP_NEEDS_GNU_CXX_NAMESPACE=1
CCCFLAGS=-Wall -fPIC -fexceptions -frtti -pthread -fno-strict-aliasing -g -O2 -DNDEBUG -DP_NEEDS_GNU_CXX_NAMESPACE=1
INCLUDES=-I/usr/include/python2.5 -I./pycxx-5-maint/CXX
CXX=./pycxx-5-maint/CXX/Src
CC=g++ -c
CXX_OBJECTS=cxxsupport.o cxx_extensions.o cxxextensions.o IndirectPythonInterface.o
LDSHARED=g++ -shared
LDLIBS=-llemur
PYMER=pymer.o index_environment.o

CCCFLAGS+=-DPACKAGE_NAME=\"Lemur\" -DPACKAGE_TARNAME=\"lemur\" -DPACKAGE_VERSION=\"4.9\" -DPACKAGE_STRING=\"Lemur\ 4.9\" -DPACKAGE_BUGREPORT=\"project@lemurproject.org\" -DYYTEXT_POINTER=1 -DHAVE_LIBM=1 -DHAVE_LIBPTHREAD=1 -DHAVE_LIBZ=1 -DHAVE_NAMESPACES= -DISNAN_IN_NAMESPACE_STD= -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -D_FILE_OFFSET_BITS=64 -DHAVE_FSEEKO=1 -DHAVE_MKSTEMP=1 -DHAVE_EXT_ATOMICITY_H=1 -DP_NEEDS_GNU_CXX_NAMESPACE=1 -DNDEBUG=1


all : pymer.so

pymer.so : $(CXX_OBJECTS) $(PYMER)
	$(LDSHARED) $(LDLIBS) $(CCCFLAGS) $(CXX_OBJECTS) $(PYMER) -o $@

cxxsupport.o : $(CXX)/cxxsupport.cxx
	$(CC) $(CCCFLAGS) $(INCLUDES) $< -o $@
cxxextensions.o : $(CXX)/cxxextensions.c
	$(CC) $(CCFLAGS) $(INCLUDES) $< -o $@
cxx_extensions.o : $(CXX)/cxx_extensions.cxx
	$(CC) $(CCCFLAGS) $(INCLUDES) $< -o $@
IndirectPythonInterface.o : $(CXX)/IndirectPythonInterface.cxx
	$(CC) $(CCCFLAGS) $(INCLUDES) $< -o $@
pymer.o : pymer.cpp
	$(CC) $(CCCFLAGS) $(INCLUDES) $< -o $@
index_environment.o : index_environment.cpp
	$(CC) $(CCCFLAGS) $(INCLUDES) -llemur $< -o $@	

clean:
	rm -f *.o *.so