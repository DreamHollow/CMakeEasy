# CMakeEasy
A terminal-based CMakeLists.txt generator.

BRANCHES
----------------

CMakeEasy is configured to generate CMakeLists.txt files for applications, but not libraries.

`master` holds the final, stable changes to CMakeEasy.
`devel` branches or numbered branches such as `1.2.x` are in-development and not considered safe for general use. 

NOTE: Branch versioning numbering has been revised. Project will start officially as 1.0.

IMPORTANT NOTICE
----------------

This program is designed to be considerably different between "release states" with early releases having much fewer features.

As per the Unlicense, you can do whatever you want with this code.
It is completely in the public domain.

It can be confusing because this project's name is so similar to the actual CMake. Be advised:

**CMakeEasy has 'CMake' in the name but is NOT directly attributed to or endorsed by the CMake developers.**

**This is a passion project developed independently to make CMake more accessible to struggling programmers.**

**>CMake itself< is licensed under the OSI-approved BSD 3-clause License and is NOT public domain!!**

*CMakeEasy* is a program that is designed to procedurally generate an automatic CMakeLists.txt file for inexperienced users who aren't familiar the format of CMake. As such, it should be known that the developers on this project are not necessarily associated with CMake.

CMakeEasy runs best with CMake version 2.24.2 and may not work with older versions.

Addendum: Because CMakeEasy requires access to your file system to work as intended, this program may ask for administrative rights.
At this point in time, this is the only way to create the CMakeEasy binary for most systems.

HOW IT WORKS
------------

The program's design is extremely simple.

CMakeEasy contains NO dependencies. Everything it needs is built-in directly.
The program overall was designed for lightweight performance in mind. Most variable and data types used are meant to consume as little memory as possible,
while still providing optimal performance and safety.

It will take in raw text output provided by the user, configure it into a format for a CMakeLists.txt file, then produce the file in a directory.

If you have difficulties compiling your program, please raise an issue to the CMakeEasy team.

This program currently has no dependencies and should work fine if all the relevant files are included.

Any code that is commented out is still being evaluated and tested.

You may uncomment the code if you wish, but please keep in mind that this code is not guaranteed to work.

CMakeEasy saves CMakeLists.txt files to your $HOME folder.
This means that the current user should see CMakeLists.txt appear along with
'Documents' 'Pictures' etc.

If this does not happen, please raise an issue on GitHub and explain what happened as you ran the program.

DOCUMENTATION
-----------

The documentation on how to use CMakeEasy is formatted to be read by a web browser.

If the included documentation isn't helpful to you, please raise an issue on the Git repo
and explain what could be done to better explain the program's functionality.

CMakeEasy is intended to make the generation of CMakeLists.txt files as painless as possible.
Let us know if something is wrong!

COMPILATION
-----------

If you need to compile CMakeEasy, it should be done as follows.

CMakeEasy can be compiled with it's own CMakeLists.txt file. As to make this less confusing, the provided CMakeLists.txt file should be set to "read-only" once downloaded.

The CMakeLists.txt file that you use to compile CMakeEasy should remain in the original folder you find it in; the one for compiling CMakeEasy (/CMakeEasy).

If you want to suggest that CMakeEasy follow a different build system, please flag an issue. Thanks.

---

*THE EASY WAY*

*** If you're on Linux: ***

Currently, terminal-based CMakeEasy can be used in two different ways.
If you want to install a local version of CMakeEasy without installing it to your system, just comment out the "install" commands on your CMakeLists.txt file.

Then you should run 'build.sh' and it will generate a working debug setup.
You will have to run CMakeEasy through terminal directly in the folder.

If you cannot execute the pre-configured bash scripts like 'build.sh' and 'install.sh', then you should go to your CMakeEasy folder and use this command:

`sudo chmod +x build.sh`

It should be possible to run the CMakeEasy binary from the build folder, unless the folder is renamed.

`run.sh`

IMPORTANT:
`install.sh` should automatically create a build folder, which makes it possible to install the binary.

Sometimes the CMake cache gets confused and will fail to install CMakeEasy properly.

Once you've made sure to build the binary, 
then you can safely use the script
`sudo ./install.sh`
should install CMakeEasy fully to your system.

Then you can run CMakeEasy straight from your terminal like any other program.

This is a much faster way than manually typing out the build/make commands.

*THE COMPLEX WAY*

Make sure you have CMake installed and make sure you have the original CMakeLists.txt file that came with the git repo.

If you get confused about which one that is, make sure it says the project name is "CMakeEasy VERSION 1.0"

Once you're sure you have the right one, just open up a Terminal in your CMakeEasy folder.

Then enter:
`cmake -S . -B Debug` to build the project to a Debug folder.

Go to your bin/build folder. Please run your 'make' command as a superuser, or the program may not compile.
`sudo make`

Then enter your credentials.

*** If you're on Windows: ***

FOR VISUAL STUDIO
-----------

Download the CMakeEasy project however you please, but it is strongly
advised that you use either Git For Windows or GitHub Desktop.

Clone the CMakeEasy repo to your local system or download the ZIP file.

Open Powershell in Administrator mode and navigate to your CMakeEasy directory.
Another way to do this is to run Visual Studio with Administrative rights and open the Command Line Tool.

Use this command to build CMakeEasy, you will need administration rights for this process to fully work:

`cmake -S . -B Debug`

This should generate the relevant build files to that folder.
For Visual Studio you should see a few different build types. For installation, you will want to open the CMakeEasy.sln file with Administrative rights again.

Select the INSTALL build setup from your solution view in Visual Studio and right click, then build it.

If you have administrative rights, this process should fully build the program and install CMakeEasy to your 'Program Files' folder on your hard drive.

Because CMakeEasy requires administrator permission to create and edit CMakeLists.txt files, you will have to enable "run as Administrator" for the CMakeEasy binary to fully work.
If you do not do this, you may encounter a system warning that says "Access Denied" or something similar. CMakeEasy will also warn you that a file path could not be accessed.
