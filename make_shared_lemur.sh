#!/bin/bash
LIB=/usr/local/lib

##########################################
if [ "$(whoami)" != "root" ]; then
    echo "You must run this script as root."
    exit
fi

if [ -e "$LIB/liblemur.a" ]; then
    echo found liblemur.a
else
    echo Cannot find liblemur.a - find it, then specify the location in $0
    exit
fi

TMPDIR=$(mktemp -d)
cd $TMPDIR
echo Copying $LIB/liblemur.a to $TMPDIR ....
cp $LIB/liblemur.a .

echo Extracting liblemur....
ar x liblemur.a
rm main.o

echo Creating dynamically shared library...
g++ -shared *.o -o liblemur.so.0.0.0

echo Installing library...
rm -f $LIB/liblemur.so*
cp liblemur.so.0.0.0 $LIB
rm -rf $TMPDIR
ln -s $LIB/liblemur.so.0.0.0 $LIB/liblemur.so.0
ln -s $LIB/liblemur.so.0.0.0 $LIB/liblemur.so

echo Done.