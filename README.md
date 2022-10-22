# CMakeEasy
A terminal-based CMakeLists.txt generator.

IMPORTANT NOTICE
----------------

This is an in-progress program so not all of the features are finished and it's impossible to know what the final release will look like.

As per the Unlicense, you can do whatever you want with this code.
It is completely in the public domain.

**CMakeEasy has 'CMake' in the name but is NOT directly attributed to or endorsed by the CMake developers.**

It is simply a program that is designed to procedurally generate an automatic CMakeLists.txt file for inexperienced users who aren't familiar the format of CMake. As such, it should be known that the developers on this project are not necessarily associated with CMake.

CMakeEasy runs best with the latest version of CMake (2.24.2) and may sometimes be problematic with older versions.

HOW IT WORKS
------------

The program's design is extremely simple.

It will take in raw text output provided by the user, configure it into a format for a CMakeLists.txt file, then produce the file in a directory.

**CMakeEasy is confirmed to work on a very basic level as of now.

If you have difficulties compiling your program, please raise an issue to the CMakeEasy team.**

This program currently has no dependencies and should work fine if all the relevant files are included.

Any code that is commented out is still being evaluated and tested.

You may uncomment the code if you wish, but please keep in mind that this code is not guaranteed to work.

COMPILATION
-----------

If you need to compile CMakeEasy, it should be done as follows.

**If you're on Linux (Ubuntu/Debian):**
Open up Terminal.
Make sure you have the GNU C++ compiler (g++) installed.

The bash script included with the source code will check for a g++ installation, but if you aren't using standard directories then it won't work.

The included script 'compile.sh' can run with bash and automatically compile the program.

NOTICE: Be careful with shell files in general.
They can directly execute commands through your Linux terminal.

To compile, run `bash compile.sh`

Then to run CMakeEasy, enter:

`./CMakeEasy`

**If you're on Windows:**
(Still working on this section, sorry!)
