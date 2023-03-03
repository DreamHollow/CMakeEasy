#! /bin/sh

echo "Building CMakeEasy...\n"
cmake -S . -B build
cd build
make
echo "\nBuilt CMakeEasy in directory /build"