#include "AltString.hpp"

AltString::AltString()
{

};

AltString::~AltString()
{

};

void AltString::init_vars()
{
    this->is_command = false;
};

/// @brief Displays at the very beginning of the program.
/// It functions as a welcome screen and documentation reference.
void AltString::start()
{
    std::cout << "Welcome to the CMakeLists all-purpose generator!" << "\n";
    std::cout << "This generator will help further simplify CMakeLists.txt generation" << "\n";
    std::cout << "for inexperienced users." << "\n";
    std::cout << "\n";
    std::cout << "This program will not tell you how to use CMake. Learning proper CMake" << "\n";
    std::cout << "usage requires that you read the documentation at " << "\n";
    std::cout << "https://cmake.org/documentation/" << "\n";
    std::cout << "\n";
    std::cout << "Please keep in mind that incorrect inputs will force the program to" << "\n";
    std::cout << "terminate prematurely." << "\n";
    std::cout << "\n";
    std::cout << "This version of CMakeEasy works exclusively for" << "\n";
    std::cout << "configuring CMake to work with C++ files." << "\n";
    std::cout << "\n";
    std::cout << "You will be asked what version of CMake you are using." << "\n";
    std::cout << "A major and minor version of the program must be provided." << "\n";
    std::cout << "This will designate the 'minimum version' needed for things to work." << "\n";
    std::cout << "\n";
    std::cout << "What is the major version of CMake that you are using?" << "\n";
    std::cout << "Example: [3].24.2" << "\n";
    std::cout << "\n";
};

void AltString::minor_vers()
{
    std::cout << "\n";
    std::cout << "What is the minor version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.[24].2" << "\n";
    std::cout << "\n";
};

void AltString::release_vers()
{
    std::cout << "\n";
    std::cout << "What is the release version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.24.[2]" << "\n";
};

void AltString::program_vers()
{
    std::cout << "Would you like to add a program version? Example: project(MyProgram VERSION 1.0)" << "\n";
    std::cout << "1. Yes, add a version number." << "\n";
    std::cout << "2. No, leave as-is." << "\n";
};

/// @brief Displays most recent C++ Standards.
void AltString::standard()
{
    std::cout << "Please set the standard for your C++ application." << "\n";
    std::cout << "\n";
    std::cout << "If you're not using any newer C++ standards, you can select option 4." << "\n";
    std::cout << "\n";
    std::cout << "This list may be updated in the future as more standards are added." << "\n";
    std::cout << "1. C++20" << "\n";
    std::cout << "2. C++17" << "\n";
    std::cout << "3. C++14" << "\n";
    std::cout << "4. Not following standard, N/A" << "\n";
};

/// @brief Displays information about source files, including class inputs.
void AltString::source()
{
    std::cout << "Please set the 'source files' that allow your program to run." << "\n";
    std::cout << "Source files are necessary for your program to run." << "\n";
    std::cout << "They are NOT libraries." << "\n";
    std::cout << "Example: main.cpp" << "\n";
};

/// @brief Checks iostream input. It will force the program to stop
/// if the input fails or doesn't match the type.
/// @return Success (0) or Failure (1)
int AltString::entry_fail()
{
    if(std::cin.fail())
    {
        std::cout << "\n";
        std::cout << "-- ERROR: INVALID INPUT --" << "\n";
        std::cout << "\n";
        std::cout << "Sorry, the program encountered an error." << "\n";
        std::cout << "This error message is encountered if input was considered unsafe" << "\n";
        std::cout << "for the program to process." << "\n";
        std::cout << "\n";
        std::cout << "If you don't understand why you have this error," << "\n";
        std::cout << "please raise an issue on the Github repository." << "\n";
        std::cout << "\n";
        std::cout << "Thank you." << "\n";
        std::cout << "\n";

        return 1; // Input error
    }

    return 0; // Continue
};

// Not sure if this is even necessary, entry_fail seems to catch most errors.

/*

/// @brief Checks a string length to determine if the input is too large.
/// @param length 
/// @param max 
/// @return 
int AltString::array_fail(int length, int max)
{
    if(length > max)
    {
        std::cout << "-- ERROR: INVALID ARRAY --" << "\n";
        std::cout << "\n";
        std::cout << "Sorry, but the data you have entered is" << "\n";
        std::cout << "too big for the input buffer." << "\n";
        std::cout << "\n";
        std::cout << "Specific sizes are mentioned before input" << "\n";
        std::cout << "to prevent buffer/array overflow." << "\n";
        std::cout << "\n";
        std::cout << "If you continue to have this problem," << "\n";
        std::cout << "please contact the development team." << "\n";
        std::cout << "\n";
        std::cout << "This program will now terminate." << "\n";

        return 1;
    }

    // If the array length is less than the max size of the array
    return 0;
};

*/