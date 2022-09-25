#include "Manager.hpp"

// Most of the actual program is just explanation
// Sorry about the mess - DH

int entry_fail();

int main()
{
    Manager ext_file;

    bool debugging = true;
    bool valid_stand = false;

    // Strings
    // const std::string filename = "CMakeLists.txt";
    char project_name[64]; // Use character arrays for stability
    char exe_name[64];
    std::string declaration;

    // Shorts used to avoid unnecessary memory allocation
    // These are recycled exactly once
    short major = 0;
    short minor = 0;
    short release = 0;

    short standard = 0;
    short prog_vers = 0;

    short num_sources = 0;

    std::cout << "Welcome to the CMakeLists all-purpose generator!" << "\n";
    std::cout << "This generator will help further simplify CMakeLists.txt generation" << "\n";
    std::cout << "for inexperienced users." << "\n";
    std::cout << "\n";
    std::cout << "Please keep in mind that incorrect inputs will force the program to" << "\n";
    std::cout << "terminate prematurely." << "\n";
    std::cout << "\n";
    std::cout << "Please keep in mind that this version of CMakeEasy works exclusively for" << "\n";
    std::cout << "configuring CMake to work with C++ files." << "\n";
    std::cout << "\n";
    std::cout << "You will be asked what version of CMake you are using." << "\n";
    std::cout << "A major and minor version of the program must be provided." << "\n";
    std::cout << "This will designate the 'minimum version' needed for things to work." << "\n";
    std::cout << "\n";
    std::cout << "What is the major version of CMake that you are using?" << "\n";
    std::cout << "Example: [3].24.2" << "\n";
    std::cout << "Your version: ";
    std::cin >> major;

    if(entry_fail() != 0)
    {
        return 1;
    }

    // Version numbering (CMake)

    std::cout << "\n";
    std::cout << "What is the minor version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.[24].2" << "\n";
    std::cout << "Your version: ";
    std::cin >> minor;

    if(entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";
    std::cout << "What is the release version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.24.[2]" << "\n";
    std::cout << "Your version: ";
    std::cin >> release;

    if(entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "Configuring line inputs..." << "\n";
    std::cout << "You have designated your version of CMake as ";
    std::cout << major << "." << minor << "." << release << "\n";
    std::cout << "\n";
    std::cout << "Please keep in mind that if this is wrong," << "\n";
    std::cout << "you will have to start this process over." << "\n";

    // Start writing actual CMakeFile
    std::cout << "\n";
    std::cout << "Saving " << ext_file.name() << " to your current directory..." << "\n";

    ext_file.write("cmake_minimum_required(VERSION ");
    ext_file.write(major);
    ext_file.write(".");
    ext_file.write(minor);
    ext_file.write(".");
    ext_file.write(release);
    ext_file.write(")");
    ext_file.write("\n");

    if(debugging)
    {
        std::cout << "DEBUG:" << "\n";
        std::cout << "Line in file should read as" << "\n";
        std::cout << "'cmake_minimum_required(VERSION x.x.x')" << "\n";
        std::cout << "\n";
    }

    std::cout << "Wrote 'cmake_minimum_required' line automatically." << "\n";
    std::cout << "\n";

    std::cout << "\n";
    std::cout << "Please enter the name of the project that you are trying to create." << "\n";
    std::cout << "\n";
    std::cout << "The input will only handle up to 64 characters, please don't abuse it!" << "\n";
    std::cout << "\n";
    std::cout << "Your project name: ";
    std::cin.ignore();
    std::cin.getline(project_name,64);

    if(entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";
    std::cout << "Your project's name has been evaluated as '" << project_name;
    std::cout << "', and will be saved as such." << "\n";
    std::cout << "\n";

    ext_file.write("project(");
    ext_file.write(project_name);

    major = 0;
    minor = 0;

    std::cout << "Would you like to add a program version? Example: project(MyProgram VERSION 1.0)" << "\n";
    std::cout << "1. Yes, add a version number." << "\n";
    std::cout << "2. No, leave as-is." << "\n";
    std::cout << "Your choice: ";
    std::cin >> prog_vers;

    std::cout << "\n";

    if(entry_fail() != 0)
    {
        return 1;
    }

    if(prog_vers == 1)
    {
        std::cout << "Please enter the major version number for your program." << "\n";
        std::cout << "Example: [1].0" << "\n";
        std::cout << "Your version: ";
        std::cin >> major;

        if(entry_fail() != 0)
        {
            return 1;
        }

        std::cout << "Please enter the minor version number for your program." << "\n";
        std::cout << "Example: 1.[0]" << "\n";
        std::cout << "Your version: ";
        std::cin >> minor;

        if(entry_fail() != 0)
        {
            return 1;
        }

        ext_file.write(" ");
        ext_file.write("VERSION ");
        ext_file.write(major);
        ext_file.write(".");
        ext_file.write(minor);
        ext_file.write(")");

        std::cout << "\n";
    }
    else if(prog_vers == 2)
    {
        std::cout << "Understood. No version number will be added to your program build at this time." << "\n";
        std::cout << "\n";

        ext_file.write(")");
    }
    else
    {
        std::cout << "Sorry, that is not a valid list choice." << "\n";
        std::cout << "Defaulting to choice 2, no program version will be added." << "\n";
        std::cout << "\n";
    }

    ext_file.write("\n"); // Formats next line no matter what

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "DEBUG:" << "\n";
        std::cout << "Line in file should read as" << "\n";
        std::cout << "'project(" << project_name;

        if(major != 0 || minor != 0)
        {
            std::cout << " ";
            std::cout << "VERSION " << major << "." << minor << ")";
        }
        else
        {
            std::cout << ")'";
        }
        std::cout << "\n";
    }

    // Setting modern C++ standards

    std::cout << "Please set the standard for your C++ application." << "\n";
    std::cout << "\n";
    std::cout << "If you're not using any newer C++ standards, you can select option 4." << "\n";
    std::cout << "\n";
    std::cout << "This list may be updated in the future as more standards are added." << "\n";
    std::cout << "1. C++20" << "\n";
    std::cout << "2. C++17" << "\n";
    std::cout << "3. C++14" << "\n";
    std::cout << "4. Not following standard, N/A" << "\n";
    std::cout << "Your standard: ";
    std::cin.clear();
    std::cin >> standard;

    std::cout << "\n";

    if(entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";

    switch(standard)
    {
        case 0:
        {
            valid_stand = false;

            std::cout << "This is not a valid choice." << "\n";
            std::cout << "Your standard will be configured to the default." << "\n";
            standard = 4;
            if(debugging)
            {
                std::cout << "\n";
                std::cout << "DEBUG:";
                std::cout << "'standard' was assigned to the number 4." << "\n";
                std::cout << "\n";
            }
            break;
        }
        case 1:
        {
            valid_stand = true;

            std::cout << "Configuring file for C++20 standards..." << "\n";
            declaration = "CMAKE_CXX_STANDARD 20";
            break;
        }
        case 2:
        {
            valid_stand = true;

            std::cout << "Configuring file for C++17 standards..." << "\n";
            declaration = "CMAKE_CXX_STANDARD 17";
            break;
        }
        case 3:
        {
            valid_stand = true;

            std::cout << "Configuring file for C++14 standards..." << "\n";
            declaration = "CMAKE_CXX_STANDARD 14";
            break;
        }
        case 4:
        {
            valid_stand = false;

            std::cout << "Standards not set; default C++ standards will be implemented." << "\n";
            break;
        }
        default:
        {
            valid_stand = false;

            std::cout << "The provided input is not part of the existing list." << "\n";
            std::cout << "Standards not set; default C++ standards will be implemented." << "\n";
            break;
        }
    }

    if(valid_stand)
    {
        ext_file.write("set(");
        ext_file.write(declaration);
        ext_file.write(")");
        ext_file.write("\n");
    }

    if(debugging)
    {
        if(valid_stand)
        {
            std::cout << "DEBUG:" << "\n";
            std::cout << "Line in file should read as" << "\n";
            std::cout << "'set(" << declaration << ")'" << "\n";
            std::cout << "\n";
        }
        else
        {
            std::cout << "DEBUG:" << "\n";
            std::cout << "Declaration was either invalid or not assigned." << "\n";
        }
    }

    std::cout << "\n";

    // Setting subdirectories

    // TO-DO

    // Setting source files
    // and so much more!

    // Add executable

    std::cout << "Please set the 'source files' that allow your program to run." << "\n";
    std::cout << "Source files are necessary for your program to run." << "\n";
    std::cout << "They are NOT libraries." << "\n";
    std::cout << "Example: main.cpp" << "\n";

    std::cout << "\n";

    num_sources = 1; // Required

    std::cout << "Please enter the name of your main executable, along with .cpp: ";
    std::cin.ignore();
    std::cin.getline(exe_name, 64);

    std::cout << "\n";

    ext_file.write("add_executable(${PROJECT_NAME}");
    ext_file.write(" ");
    ext_file.write(exe_name);
    // Extra files - TODO
    ext_file.write(")");

    ext_file.write("\n");

    if(entry_fail() != 0)
    {
        return 1;
    }

    // Enter more necessary files
    // - TODO

    if(debugging)
    {
        std::cout << "DEBUG:" << "\n";
        std::cout << "Line in file should read as" << "\n";
        std::cout << "add_executable(${PROJECT_NAME} ";
        std::cout << exe_name;
        std::cout << ")" << "\n";
    }

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "DEBUG: File closed." << "\n";
        std::cout << "\n";
        std::cout << "DEBUG:" << "\n";
        std::cout << "Reached end of program." << "\n";
    }

    return 0;
};

int entry_fail()
{
    if(std::cin.fail())
    {
        std::cout << "\n";
        std::cout << "Sorry, the program encountered an error." << "\n";
        std::cout << "This error message is encountered if input was considered unsafe" << "\n";
        std::cout << "for the program to process." << "\n";
        std::cout << "\n";
        std::cout << "If you don't understand why you have this error," << "\n";
        std::cout << "please report the error to the developer at their" << "\n";
        std::cout << "primary contact address." << "\n";
        std::cout << "\n";

        return 1; // Input error
    }

    return 0; // Continue
};
