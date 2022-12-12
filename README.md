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

** Current version has disabled moving CMakeLists.txt to another folder,
sorry for any inconvenience. **

HOW IT WORKS
------------

The program's design is extremely simple.

CMakeEasy contains NO dependencies. Everything it needs is built-in directly.

It will take in raw text output provided by the user, configure it into a format for a CMakeLists.txt file, then produce the file in a directory.

**CMakeEasy is confirmed to work on a very basic level as of now.

If you have difficulties compiling your program, please raise an issue to the CMakeEasy team.**

This program currently has no dependencies and should work fine if all the relevant files are included.

Any code that is commented out is still being evaluated and tested.

You may uncomment the code if you wish, but please keep in mind that this code is not guaranteed to work.

COMPILATION
-----------

If you need to compile CMakeEasy, it should be done as follows.

AS OF OCTOBER 2022 -
CMakeEasy can now be compiled with CMake itself.

This can be a bit confusing due to the nature of the program, so here's a detailed explanation to prevent confusion.

The CMakeLists.txt file you find in the very first folder 'CMakeEasy' is part of building the program itself. It should not be modified if you follow the instructions.

The CMakeLists.txt file that you use to compile CMakeEasy should remain in the original folder you find it in; the one for compiling CMakeEasy (/CMakeEasy) and the one that is generated by the program (/CMakeEasy/bin/build).

---

Make sure you have CMake installed and make sure you have the original CMakeLists.txt file that came with the git repo.

If you get confused about which one that is, make sure it says the project name is "CMakeEasy VERSION 1.1"

Once you're sure you have the right one, just open up a Terminal in your CMakeEasy folder.

Then enter:
`cmake -S . -B bin/build`

Please do NOT set your -B directory in the same place as the source "CMakeEasy" folder, it will cause issues and potentially overwrite the default CMakeLists.txt file.

Make sure it is `bin/build`

Go to your bin/build folder and run make:
`make`

** If you're on Linux: **

If everything was done correctly, CMakeEasy should exist as an executable in your CMakeEasy/bin/build folder.

Then to run CMakeEasy, open up the build folder and start a Terminal.
Then use the following command:

`./CMakeEasy`

** If you're on Windows: **

FOR VISUAL STUDIO
-----------

Download the CMakeEasy project however you please, but it is strongly
advised that you use either Git For Windows or GitHub Desktop.

Clone the CMakeEasy repo to your local system.

Once the project has been cloned to a directory, open that directory
up inside of Visual Studio. As of VS 2022, compilation can be slightly
problematic. If you have trouble with VS trying to read the CMakeLists.txt
file, you should do this:

Go to Tools > Command Line > Command Prompt

In the Command Prompt (make sure it's in the CMakeEasy folder!!),
Follow similar instructions to Linux.

`cmake -S . -B bin/build`

This should generate the relevant build files to that folder.

If Visual Studio will not allow you to access the bin/build folders,
simply edit the .gitignore file and comment out the bin/build line.

Please remember to uncomment this line if you plan to stage changes.
The bin/build folders should NOT be committed to the repo.

You should have several Visual Studio files available to you after
generation. If not, something may have gone wrong during using the
Command Prompt. Please go back and try it again, to see if it
fixes the problem.

Once everything is working properly, it should be possible to generate
at least a Debug installation of the program.
