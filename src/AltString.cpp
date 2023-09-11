#include "AltString.hpp"

// Potential TODO: Convert all void functions into large void function with switch statement.

AltString::AltString()
{
    init_vars();
};

AltString::~AltString()
{
    free_data();
};

/// @brief Called to guarantee vector clearing.
void AltString::free_data()
{
    declarations.clear();
    declarations.shrink_to_fit();
    commands.clear();
    commands.shrink_to_fit();

    std::cout << db_msg("AltString: Freed vectors.\n");
};

void AltString::init_vars()
{
    is_command = false;

   std::cout << db_msg("Initializing declarations...\n");

    // Declarations
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
    declarations.push_back("REQUIRED"); // 17
    declarations.push_back("COMPONENTS"); // 18
    declarations.push_back("find_package"); // 19
    declarations.push_back("CMAKE_VERBOSE_MAKEFILE"); // 20

    // Commands
    commands.push_back("message"); // 21
    commands.push_back("install"); // 22
    commands.push_back("file"); // 23

    std::cout << db_msg("Declarations initialized.\n");
};

void AltString::show_commands()
{
    std::cout << "\n";
    std::cout << "Common CMake commands:\n";
    std::cout << "\n";
    for(auto it : commands)
    {
        std::cout << it;
        std::cout << "\n";
    }

    std::cout << "\n";
}

/*
/// @brief Designed to read text explanations.
/// @param text_name
void AltString::read_segment(std::string text_name)
{
    std::ifstream in_file; // Text file to be read.

    try
    {
        in_file.open(text_name);

        if(in_file.fail())
        {
            std::cout << "\n";
            std::cout << "-- ERROR: UNABLE TO OPEN ALTSTRING DATA --" << "\n";
            std::cout << "\n";
            std::cout << "CMakeEasy was unable to read a vital program file." << "\n";
            std::cout << "Please check that all text documents are present in" << "\n";
            std::cout << "your system. For Linux, this is /usr/local/etc" << "\n";
            std::cout << "\n";
            std::cout << "For Windows users, these text files should be present" << "\n";
            std::cout << "in a folder called 'plaintext'." << "\n";

            throw "File could not be read!";
        }
        else
        {
            // Read the file data as a set of strings
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what();
    }
};
*/

/// @brief Because CMake parameters are generally reusable, this function is called.
/// @param num 
/// @return
const std::string AltString::declare(int num)
{
    return declarations.at(num);
}