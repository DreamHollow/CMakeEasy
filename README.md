# CMakeEasy
A terminal-based CMakeLists.txt generator.

BRANCHES
----------------

CMakeEasy's "master" branch is configured to generate CMakeLists.txt files for applications, but not libraries.

A branch is being worked on that will allow CMakeEasy to generate relevant
CMakeLists.txt files for libraries as well.

Please use the "master" branch if you only need to generate a configuration file for applications only.

The "visual" branch has been created and will feature a fully GUI supported version of CMakeEasy using the SFML library.

IMPORTANT NOTICE
----------------

This program is designed to be considerably different between "release states" with the 1.0 release being stable and functional, but lacking more advanced features.

As per the Unlicense, you can do whatever you want with this code.
It is completely in the public domain.

It can be confusing because this project's name is so similar to the actual CMake. Be advised:

**CMakeEasy has 'CMake' in the name but is NOT directly attributed to or endorsed by the CMake developers.**

**This is a passion project developed independently to make CMake more accessible to struggling programmers.**

**>CMake itself< is licensed under the OSI-approved BSD 3-clause License and is NOT public domain!!**

*CMakeEasy* is a program that is designed to procedurally generate an automatic CMakeLists.txt file for inexperienced users who aren't familiar the format of CMake. As such, it should be known that the developers on this project are not necessarily associated with CMake.

CMakeEasy runs best with the latest version of CMake (2.24.2) and may sometimes be problematic with older versions.

HOW IT WORKS
------------

The program's design is extremely simple.

CMakeEasy contains NO dependencies. Everything it needs is built-in directly.
The program overall was designed for lightweight performance in mind. Most variable and data types used are meant to cosume as little memory as possible,
while still providing optimal performance and safety.

It will take in raw text output provided by the user, configure it into a format for a CMakeLists.txt file, then produce the file in a directory.

If you have difficulties compiling your program, please raise an issue to the CMakeEasy team.**

This program currently has no dependencies and should work fine if all the relevant files are included.

Any code that is commented out is still being evaluated and tested.

You may uncomment the code if you wish, but please keep in mind that this code is not guaranteed to work.

CMakeEasy saves CMakeLists.txt files to your $HOME folder.
This means that the current user should see CMakeLists.txt appear along with
'Documents' 'Pictures' etc.

If this does not happen, please raise an issue on GitHub and explain what happened as you ran the program.

COMPILATION
-----------

If you need to compile CMakeEasy, it should be done as follows.

AS OF OCTOBER 2022 -
CMakeEasy can now be compiled with CMake itself.

This can be a bit confusing due to the nature of the program, so here's a detailed explanation to prevent confusion.

The CMakeLists.txt file you find in the very first folder 'CMakeEasy' is part of building the program itself. It should not be modified if you follow the instructions.

The CMakeLists.txt file that you use to compile CMakeEasy should remain in the original folder you find it in; the one for compiling CMakeEasy (/CMakeEasy) and the one that is generated by the program (/CMakeEasy/bin/build).

If you want to suggest that CMakeEasy follow a different build system, please flag an issue. Thanks.

---

*THE EASY WAY*

*** If you're on Linux: ***

Currently, CMakeEasy can be used in two different ways.
If you want to install a local version of CMakeEasy without installing it to your system, just remove the "install" commands on your CMakeLists.txt file.

Then you should run 'build_db.sh' and it will generate a working debug setup.
You will have to run CMakeEasy through terminal directly in the folder.

If you cannot execute the pre-configured bash scripts like 'build_db.sh' and 'install.sh', then you should go to your CMakeEasy folder and use this command:

`sudo chmod +x build_db.sh`

The build_db script automatically creates the CMakeEasy binary.

If you are a super user, using
`sudo ./install.sh`
should install CMakeEasy fully to your system.

Then you can run CMakeEasy straight from your terminal like any other program.

This is a much faster way than manually typing out the build/make commands.

*THE COMPLEX WAY*

Make sure you have CMake installed and make sure you have the original CMakeLists.txt file that came with the git repo.

If you get confused about which one that is, make sure it says the project name is "CMakeEasy VERSION 1.0"

Once you're sure you have the right one, just open up a Terminal in your CMakeEasy folder.

Then enter:
`cmake -S . -B build`

Go to your bin/build folder. Please run your 'make' command as a superuser, or the program may not compile.
`sudo make`

Then enter your credentials.

*** If you're on Windows: ***


*** NOTE: THIS IS CURRENTLY NOT FUNCTIONAL, CHANGES WILL BE MADE SOON ***

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

`cmake -S . -B build`

OR

`cmake -S . -B bin/build`

This should generate the relevant build files to that folder.

If Visual Studio will not allow you to access the bin/build folders,
simply edit the .gitignore file and comment out the bin/build line.

Please remember to uncomment this line if you plan to stage changes.
**The bin/build folders should NOT be committed to the repo.**

You should have several Visual Studio files available to you after
generation. If not, something may have gone wrong during using the
Command Prompt. Please go back and try it again, to see if it
fixes the problem.
