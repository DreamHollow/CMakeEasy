#! /bin/sh
# Build 'Debug'

echo "Building CMakeEasy...\n"
cmake -S . -B build
cd build
make
echo "\nBuilt CMakeEasy in directory /build"
echo "Please do not run 'make', binary is already built."