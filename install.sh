#!/bin/sh
# Only works on Linux version!
# You must run as SU for this to actually install!

echo "Building Release version..."

mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make install

echo "Release build finished."
echo "Do not build CMakeEasy. The binary should be installed to the system."
