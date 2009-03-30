#!/bin/bash
LIB=/usr/local/lib
TMPDIR=$(mktemp -d)
cd $TMPDIR
cp /usr/local/lib/liblemur.a .
ar x liblemur.a
rm main.o
g++ -shared *.o -o liblemur.so.0.0.0
rm -f $LIB/liblemur.so*
cp liblemur.so.0.0.0 $LIB
rm -rf $TMPDIR
ln -s $LIB/liblemur.so.0.0.0 $LIB/liblemur.so.0
ln -s $LIB/liblemur.so.0.0.0 $LIB/liblemur.so

