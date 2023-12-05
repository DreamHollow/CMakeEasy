#!/bin/sh
# Use this script to run CMake from the source folder,
# not the installed version.

DIR="Debug"

echo "Attempting to run debug version of CMakeEasy..."

if [ -d "$DIR" ]
then
    cd $DIR
    ./cmakeeasy
else
    echo "ERROR: No build directory present!"
fi
