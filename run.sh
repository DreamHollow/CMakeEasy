#!/bin/sh
# Use this script to run CMake from the source folder,
# not the installed version.

echo "Attempting to run debug version of CMakeEasy..."

if [ -d 'build' ]
then
    cd build
    ./cmakeeasy
else
    echo "ERROR: No build directory present!"
fi