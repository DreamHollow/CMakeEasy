#!/bin/sh
# Only works on Linux version!
# You must run as sudo/wheel for this to actually install!

old_file="/usr/local/opt/cmakeeasy"
new_file="/usr/local/etc/cmakeeasy"
cmake_bin="/usr/bin/cmake"

# Won't allow install if CMake isn't present
if [ ! -f "$cmake_bin" ]
then
    echo "CMake was not found or not present in expected directories.";
    echo "Installation cannot continue."
    echo "\n"
    echo "ERROR MSG: CMAKE_NOT_FOUND"
    return 1
fi

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
