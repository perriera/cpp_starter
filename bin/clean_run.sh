#!/bin/bash

git pull; rm -rf build; mkdir build; cd build; cmake ..; make; cd ..; 

FILE=build/run-unittests-sisdata
if test -f "$FILE"; then
    $FILE
    echo "$FILE completed"
fi

FILE=build/run-unittests-sisdata_i386
if test -f "$FILE"; then
    $FILE
    echo "$FILE completed"
fi

