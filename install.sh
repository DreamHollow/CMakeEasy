#!/bin/sh
# Only works on Linux version!
# You must run as sudo/wheel for this to actually install!

old_file="/usr/local/opt/cmakeeasy"
new_file="/usr/local/etc/cmakeeasy"

if [ -d "$old_file" ]
then
    echo "Previous directory '$old_file' no longer in use."
    echo "Updating directory to '$new_file'..."
    # Remove obsolete directory
    rm -r $old_file
    echo "Obsolete directory '$old_file' removed."
    echo "\n"
else
    echo "No previous directory '$old_file' found on this device."
    echo "Continuing normal install."
    echo "\n"
fi

echo "Building Release version..."

cmake -S . -B build

mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make install

echo "Release build finished."
echo "Do not build CMakeEasy. The binary should be installed to the system."
