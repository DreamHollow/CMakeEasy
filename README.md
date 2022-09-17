# CMakeEasy
A terminal-based CMakeLists.txt generator.

IMPORTANT NOTICE
----------------

This is an in-progress program so not all of the features are finished and it's impossible to know what the final release will look like.
As per the Unlicense, you can do whatever you want with this code.

**CMakeEasy has 'CMake' in the name but is NOT directly attributed to or endorsed by the CMake developers.**

It is simply a program that is designed to procedurally generate an automatic CMakeLists.txt file for inexperienced users who aren't familiar the format of CMake. As such, it should be known that the developers on this project are not necessarily associated with CMake.

HOW IT WORKS
------------

The program's design is extremely simple.

It will take in raw text output provided by the user, configure it into a format for a CMakeLists.txt file, then produce the file in a directory.
