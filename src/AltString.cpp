#include "AltString.hpp"

// Potential TODO: Convert all void functions into large void function with switch statement.

AltString::AltString()
{
    init_vars();
};

AltString::~AltString()
{
    declarations.clear();
    declarations.shrink_to_fit();
};

void AltString::init_vars()
{
    is_command = false;

    declarations.push_back("cmake_minimum_required"); // 0
    declarations.push_back("project"); // 1
    declarations.push_back("VERSION"); // 2
    declarations.push_back("LANGUAGES CXX"); // 3
    declarations.push_back("configure_file"); // 4
    declarations.push_back("target_link_libraries"); // 5
    declarations.push_back("CMAKE_CXX_STANDARD"); // 6
    declarations.push_back("set"); // 7
    declarations.push_back("add_executable"); // 8
    declarations.push_back("target_link_libraries"); // 9
    declarations.push_back("include_directories"); // 10
    declarations.push_back("target_compile_features"); // 11
    declarations.push_back("${PROJECT_NAME}"); // 12
    declarations.push_back("PUBLIC"); // 13
    declarations.push_back("PRIVATE"); // 14
    declarations.push_back("INTERFACE"); // 15
    declarations.push_back("CMAKE_CXX_STANDARD_REQUIRED"); // 16
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
    std::cout << "Example: [3].22.1" << "\n";
    std::cout << "\n";
};

void AltString::minor_vers()
{
    std::cout << "\n";
    std::cout << "What is the minor version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.[22].1" << "\n";
    std::cout << "\n";
};

void AltString::release_vers()
{
    std::cout << "\n";
    std::cout << "What is the release version of CMake that you are using?" << "\n";
    std::cout << "Example: 3.22.[1]" << "\n";
};

void AltString::program_vers()
{
    std::cout << "Would you like to add a program version? Example: project(MyProgram VERSION 1.0)" << "\n";
    std::cout << "1. Yes, add a version number." << "\n";
    std::cout << "2. No, leave as-is." << "\n";
};

void AltString::program_lang()
{
    std::cout << "Because this version of CMakeEasy is designed for C++ context," << "\n";
    std::cout << "The 'LANGUAGES' setting will be automatically set to 'CXX'." << "\n";
};

/// @brief Displays information about packages, link information, etc.
void AltString::package()
{
    std::cout << "If you have any packages to find, please enter them here." << "\n";
    std::cout << "\n";
    std::cout << "Packages are NOT regular directories or folders." << "\n";
    std::cout << "\n";
    std::cout << "Please note that if your package has 'components', they must" << "\n";
    std::cout << "also be added in order for the package to work." << "\n";
    std::cout << "This step will come later as the program asks for libraries," << "\n";
    std::cout << "as the program will also link the libraries and add components." << "\n";
    std::cout << "\n";
    std::cout << "Please note that not understanding how this feature works" << "\n";
    std::cout << "may result on a compilation error by CMake and possibly" << "\n";
    std::cout << "generate a non-functional CMake cache." << "\n";
};

/// @brief Displays information about CMake and how it handles operating systems.
void AltString::op_sys()
{
};

/// @brief Displays relevant C++ standards and choices.
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

/// @brief Optional CMakeEasy promotion function.
void AltString::promote()
{
    std::cout << "Would you like to promote CMakeEasy by" << "\n";
    std::cout << "Adding an auto-generated comment to the end" << "\n";
    std::cout << "of CMakeLists.txt?" << "\n";
    std::cout << "\n";
    std::cout << "1. I would like to promote this project." << "\n";
    std::cout << "2. No, I don't want to promote this project." << "\n";
    std::cout << "\n";
    std::cout << "Your choice: ";
};

/// @brief Checks iostream input. It will force the program to stop
/// if the input fails or doesn't match the type.
/// @return Success (0) or Failure (1)
int AltString::entry_fail(bool is_array)
{
    if(std::cin.fail())
    {
        std::cout << "\n";
        std::cout << "-- ERROR: INVALID INPUT --" << "\n";
        std::cout << "\n";

        if(is_array)
        {
            std::cout << "-- ERROR: ARRAY FAILURE -- " << "\n";

            std::cout << "An error occurred while entering data into a char array." << "\n";
            std::cout << "Either the wrong data or too much data was entered." << "\n";
            std::cout << "\n";
        }

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

/// @brief Displays information that helps with standardization.
void AltString::include_dirs()
{
    std::cout << "ATTENTION:" << "\n";
    std::cout << "CMakeEasy is configured to standardize C++ directories." << "\n";
    std::cout << "\n";
    std::cout << "CMakeEasy automatically assumes you are using standard directories." << "\n";
    std::cout << "The program will automatically target /include and /src directories by default." << "\n";
    std::cout << "These changes will be reflected on the CMakeLists.txt file." << "\n";
};

void AltString::package_entry()
{
        std::cout << "\n";
        std::cout << "Would you like to link any libraries?" << "\n";
        std::cout << "Please keep in mind that if CMake cannot find your library," << "\n";
        std::cout << "linking these files will not work." << "\n";
        std::cout << "\n";
        std::cout << "Please note that while adding libraries, you will need" << "\n";
        std::cout << "to link any necessary components as well." << "\n";
        std::cout << "\n";
        std::cout << "Start adding libraries?" << "\n";
        std::cout << "1. Yes." << "\n";
        std::cout << "2. No." << "\n";
        std::cout << "Your choice: ";
};

/// @brief Because CMake parameters are generally reusable, this function is called.
/// @param num 
/// @return
const std::string AltString::declare(int num)
{
    return declarations.at(num);
}