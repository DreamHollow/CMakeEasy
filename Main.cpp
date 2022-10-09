#include "Manager.hpp"
#include <memory>

int main()
{
    // Heap allocated file manager.
    std::unique_ptr<Manager> ext_file = std::make_unique<Manager>();
    Explainer tell;

    bool debugging = true;
    bool valid_stand = false;

    // const std::string filename = "CMakeLists.txt";
    char project_name[64];
    char exe_name[64];
    std::string declaration;

    // Shorts used to avoid unnecessary memory allocation

    short major = 0;
    short minor = 0;
    short release = 0;

    short standard = 0;
    // Integer used to avoid problematic char-style input.
    short yes_no = 0;

    short subdir_choice = 0;

    short num_sources = 0;
    short subdir = 0;

    tell.start();

    std::cout << "Your version: ";
    std::cin >> major;

    if(tell.entry_fail() != 0)
    {
        return 1;
    }

    // Version numbering (CMake)

    std::cout << "\n";
    std::cout << "What is the minor version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.[24].2" << "\n";
    std::cout << "Your version: ";
    std::cin >> minor;

    if(tell.entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";
    std::cout << "What is the release version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.24.[2]" << "\n";
    std::cout << "Your version: ";
    std::cin >> release;

    if(tell.entry_fail() != 0)
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
    std::cout << "Saving " << ext_file->name() << " to your current directory..." << "\n";

    ext_file->write("cmake_minimum_required(VERSION ");
    ext_file->write(major);
    ext_file->write(".");
    ext_file->write(minor);
    ext_file->write(".");
    ext_file->write(release);
    ext_file->write(")");
    ext_file->write("\n");

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

    if(tell.entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";
    std::cout << "Your project's name has been evaluated as '" << project_name;
    std::cout << "', and will be saved as such." << "\n";
    std::cout << "\n";

    ext_file->write("project(");
    ext_file->write(project_name);

    major = 0;
    minor = 0;

    std::cout << "Would you like to add a program version? Example: project(MyProgram VERSION 1.0)" << "\n";
    std::cout << "1. Yes, add a version number." << "\n";
    std::cout << "2. No, leave as-is." << "\n";
    std::cout << "Your choice: ";
    std::cin >> yes_no;

    std::cout << "\n";

    if(tell.entry_fail() != 0)
    {
        return 1;
    }

    if(yes_no == 1)
    {
        std::cout << "Please enter the major version number for your program." << "\n";
        std::cout << "Example: [1].0" << "\n";
        std::cout << "Your version: ";
        std::cin >> major;

        if(tell.entry_fail() != 0)
        {
            return 1;
        }

        std::cout << "Please enter the minor version number for your program." << "\n";
        std::cout << "Example: 1.[0]" << "\n";
        std::cout << "Your version: ";
        std::cin >> minor;

        if(tell.entry_fail() != 0)
        {
            return 1;
        }

        ext_file->write(" ");
        ext_file->write("VERSION ");
        ext_file->write(major);
        ext_file->write(".");
        ext_file->write(minor);
        ext_file->write(")");

        std::cout << "\n";
    }
    else if(yes_no == 2)
    {
        std::cout << "Understood. No version number will be added to your program build at this time." << "\n";
        std::cout << "\n";

        ext_file->write(")");
    }
    else
    {
        std::cout << "Sorry, that is not a valid list choice." << "\n";
        std::cout << "Defaulting to choice 2, no program version will be added." << "\n";
        std::cout << "\n";
    }

    ext_file->write("\n"); // Formats next line no matter what

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

    tell.standard();
    
    std::cout << "Your standard: ";
    std::cin.clear();
    std::cin >> standard;

    std::cout << "\n";

    if(tell.entry_fail() != 0)
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
        ext_file->write("set(");
        ext_file->write(declaration);
        ext_file->write(")");
        ext_file->write("\n");
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

    tell.source();

    std::cout << "\n";

    num_sources = 1; // Required

    std::cout << "Please enter the name of your main executable, along with .cpp: ";
    std::cin.ignore();
    std::cin.getline(exe_name, 64);

    std::cout << "\n";

    ext_file->write("add_executable(${PROJECT_NAME}");
    ext_file->write(" ");
    ext_file->write(exe_name);
    // Extra files - TODO
    ext_file->write(")");

    ext_file->write("\n");

    if(tell.entry_fail() != 0)
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

    // Set the subdirectories

    /*
    std::cout << "Will you use any subdirectories for your program?" << "\n";
    std::cout << "1. I will use subdirectories." << "\n";
    std::cout << "2. I will not be using subdirectories." << "\n";
    std::cout << "Your choice: ";
    std::cin >> subdir_choice;

    if(tell.entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";

    switch(subdir)
    {
        case 1:
        {
            break;
        }
        case 2:
        {
            std::cout << "No subdirectories will be added." << "\n";
            std::cout << "Skipping to next section." << "\n";
            std::cout << "\n";
            break;
        }
        default:
        {
            std::cout << "This is not a valid choice." << "\n";
            std::cout << "No subdirectories will be added." << "\n";
            std::cout << "\n";
            break;
        }
    }

    ext_file->write("\n");
    */

    // Set the libraries

    /*

    bool more_libs = false;
    
    std::cout << "Would you like to link a library or libraries?" << "\n";
    std::cout << "1. Yes, I would like to add a library or multiple libraries." << "\n";
    std::cout << "2. No, I don't need to add any libraries." << "\n";
    std::cout << "\n";
    std::cout << "Your choice: ";
    std::cin >> yes_no;

    if(tell.entry_fail() != 0)
    {
        return 1;
    }

    switch(yes_no)
    {
        case 1:
        break;
        case 2:
        break;
        default:
        break;
    }

    */

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
