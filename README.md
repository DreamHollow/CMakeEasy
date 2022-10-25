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

*** If you're on Linux ***
AS OF OCTOBER 2022 -
CMakeEasy can now be compiled with CMake itself.

This can be a bit confusing due to the nature of the program, so here's a detailed explanation to prevent confusion.

The CMakeLists.txt file that you use to compile CMakeEasy should remain in the primary folder; it is not the file you generate with the program.

When you run the program and a CMakeLists.txt file appears in the 'bin/build' folder, that is a different CMakeLists.txt file you created with CMakeEasy.

---

Make sure you have CMake installed and make sure you have the original CMakeLists.txt file that came with the git repo.

If you get confused about which one that is, make sure it says the project name is "CMakeEasy VERSION 1.0"

Once you're sure you have the right one, just open up a Terminal in your CMakeEasy folder.

Enter:
`cd bin`
`mkdir build`

Once your build folder is created, go back to your original CMakeEasy folder.

Then enter:
`cmake -S . -B bin/build`

Go to your bin/build folder and run make:
`make`

If everything was done correctly, CMakeEasy should exist as an executable in your CMakeEasy/bin/build folder.

Then to run CMakeEasy, open up the build folder and start a Terminal.
Then use the following command:

`./CMakeEasy`
