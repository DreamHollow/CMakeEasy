# CMakeEasy
A terminal-based CMakeLists.txt generator.

IMPORTANT NOTICE
----------------

This is an in-progress program so not all of the features are finished and it's impossible to know what the final release will look like.
As per the Unlicense, you can do whatever you want with this code.

**CMakeEasy has 'CMake' in the name but is NOT directly attributed to or endorsed by the CMake developers.**

It is simply a program that is designed to procedurally generate an automatic CMakeLists.txt file for inexperienced users who aren't familiar the format of CMake. As such, it should be known that the developers on this project are not necessarily associated with CMake.

CMakeEasy runs best with the latest version of CMake (2.24.2) and may sometimes be problematic with older versions.

HOW IT WORKS
------------

The program's design is extremely simple.

It will take in raw text output provided by the user, configure it into a format for a CMakeLists.txt file, then produce the file in a directory.

COMPILATION
-----------

If you need to compile CMakeEasy, it should be done as follows.

**If you're on Linux (Ubuntu/Debian):**
Open up Terminal.
Make sure you have the GNU C++ compiler (g++) installed. To check, use `g++ --version`
If it doesn't tell you the g++ version, you don't have it installed.

Just install g++ along with it's build-essentials to get things rolling.
`sudo apt install g++`

then
`sudo apt install build-essential`

Once that's done, you should be able to compile CMakeEasy from Terminal using the GNU compiler.
To do that, you should enter:

`g++ -o CMakeEasy Main.cpp Manager.cpp`

Then to run it, enter:

`./CMakeEasy`

GNU's built in Bash shell should automatically run the program on the Terminal.

*If you're on Windows:*
(Still working on this section, sorry!)
