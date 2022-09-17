#include <iostream>
#include <fstream>
#include <string>

// Most of the actual program is just explanation
// Sorry about the mess - DH

int entry_fail();

int main()
{
    bool debugging = true;

    // Strings
    const std::string filename = "CMakeLists.txt";
    char project_name[64]; // Use character array for stability

    // Shorts used to avoid unnecessary memory allocation
    short major = 0;
    short minor = 0;
    short release = 0;

    std::cout << "Welcome to the CMakeLists all-purpose generator!" << "\n";
    std::cout << "This generator will help further simplify CMakeLists.txt generation" << "\n";
    std::cout << "for inexperienced users." << "\n";
    std::cout << "\n";
    std::cout << "Please keep in mind that incorrect inputs will force the program to" << "\n";
    std::cout << "terminate prematurely." << "\n";
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
    std::cout << "Saving " << filename << " to your current directory..." << "\n";

    std::ofstream file(filename);
    if(file.is_open())
    {
        file << "cmake_minimum_required(VERSION ";
        file << major << "." << minor << "." << release << ")";
        file << "\n";

        if(debugging)
        {
            std::cout << "DEBUG:" << "\n";
            std::cout << "Line in file should read as" << "\n";
            std::cout << "'cmake_minimum_required(VERSION x.x.x')" << "\n";
            std::cout << "\n";
        }

        std::cout << "Wrote 'cmake_minimum_required' line automatically." << "\n";
        std::cout << "\n";
    }
    else
    {
        std::cout << "\n";
        std::cout << "The file could not be created or opened." << "\n";
        std::cout << "If this error persists, please contact the developer." << "\n";
        std::cout << "Thank you." << "\n";

        file.close(); // If applicable

        return 1;
    }

    std::cout << "\n";
    std::cout << "Please enter the name of the project that you are trying to create." << "\n";
    std::cout << "\n";
    std::cout << "The input will only handle up to 64 characters, please don't abuse it!" << "\n";
    std::cout << "\n";
    std::cout << "Your project name: ";
    std::cin.ignore();
    std::cin.getline(project_name,64);

    std::cout << "\n";
    std::cout << "Your project's name has been evaluated as '" << project_name;
    std::cout << "', and will be saved as such." << "\n";
    std::cout << "\n";

    if(file.is_open())
    {
        file << "project(" << project_name << ")";
        file << "\n";
    }

    if(debugging)
    {
        std::cout << "DEBUG:";
        std::cout << "Line in file should read as" << "\n";
        std::cout << "'project(" << project_name << ")'" << "\n";
        std::cout << "\n";
    }

    file.close(); // Always close the file afterwards

    if(debugging)
    {
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