#! /bin/sh
# Build 'Debug'
# You may need to be superuser to run
# This script will NOT install the program to system

cmake_bin="/usr/bin/cmake"

if [ ! -f "$cmake_bin" ]
then
    echo "CMake binary not found."
    echo "Please install CMake or check your directories."
    return 1
else
    echo "CMake binary verified, continue process..."
fi

echo "Building CMakeEasy...\n"
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build
cd build
make

echo "\nBuilt CMakeEasy in directory /build"
echo "Please do not run 'make', binary should be built."