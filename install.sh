#!/bin/sh
# Only works on Linux version!

echo "Building Release version..."

mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make install

echo "Release build finished."
echo "Do not build CMakeEasy. Binary already installed to system."
