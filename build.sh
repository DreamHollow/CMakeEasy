#!/bin/sh
# Build 'Debug'
# You may need to be superuser to run
# This script will NOT install the program to system

cmake_bin="/usr/bin/cmake"
DEBUG="Debug"

if [ ! -f "$cmake_bin" ]
then
    echo "CMake binary not found."
    echo "Please install CMake or check your directories."
    return 1
else
    echo "CMake binary verified, continue process..."
fi

echo "Building CMakeEasy...\n"
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B "$DEBUG"

if [ ! -d "$DEBUG" ]
then
    echo "ERROR: No build directory found in context!"
    echo "Unable to continue."
    echo "Please verify directory 'build' within CMakeEasy."
    return 2
else
    echo "Build directory is good, continuing...\n"
fi

cd "$DEBUG"
make

echo "Built CMakeEasy in directory /Debug"
echo "Please do not run 'make', binary should be built."
