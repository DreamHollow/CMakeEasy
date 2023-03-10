#include "Manager.hpp"

Manager::Manager()
{
  this->init_vars();
  this->init_file();
};

Manager::~Manager()
{
  free();
};

/// @brief Forces file to close to prevent leaks.
/// Outputs for debugger.
void Manager::free()
{
  this->file.close();

  if(debugging)
  {
    std::cout << db_string << "Manager closed the open file." << "\n";
  }
}

void Manager::init_vars()
{
  this->yes_no = 0;
};

/// @brief The file is initialized early into the program, along with the directory.
void Manager::init_file()
{
  if(!OS_WINDOWS) // Linux
  {
    // const char forslash = '/';

    if((homedir = getenv("HOME")) == NULL)
    {
      homedir = getpwuid(getuid())->pw_dir;
    }

    file_name = homedir + file_name;

    file_dir = file_name;
  }
  else
  {
    std::cout << "Because CMakeEasy is running in Windows, the CMakeLists.txt\n";
    std::cout << "file should output in the build directory OR relevant\n";
    std::cout << "binary directory." << "\n";
  }

  // This catch-all should really be left in for worst-case file writing scenarios.
  // If the CMakeLists.txt file cannot be accessed, it should not be written to!

  if(!this->file.is_open())
  {
    try
    {
      if(debugging)
      {
        std::cout << "\n";
        std::cout << "Warning: If CMakeListst.txt exists in /src folder," << "\n";
        std::cout << "it will be overwritten!" << "\n";
      }
      std::cout << "\n";
      std::cout << "Please remove any CMakeList.txt files that you" << "\n";
      std::cout << "Do not wish to lose." << "\n";
      std::cout << "\n";
      std::cout << "Initializing file settings..." << "\n";

      if(debugging)
      {
        std::cout << db_string << "Current file path:\n";
        std::cout << file_name << "\n";
        std::cout << db_string << "Program attempting to open file 'CMakeLists'...\n";
      }

      file.open(file_name.c_str(), std::ios::out | std::ios::trunc);

      if(file.fail())
      {
        std::cout << "The CMakeLists.txt file could not be edited." << "\n";
        std::cout << "An error occurred: 'Unusuable file path'." << "\n";

        free();
        
        throw "Bad CMakeLists directory argument.";
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }

    if(file.good())
    {
      if(debugging)
      {
        std::cout << db_string << "CMakeLists.txt is good, allowing edits." << "\n";
      }

      std::cout << "\n";
      std::cout << file_name << " is ready to be modified." << "\n";
      std::cout << "\n";
    }
  }
};

/// @brief Writes char arrays and strings into files.
/// @param context 
void Manager::write(std::string context)
{
  file << context;
};

/// @brief Converts numerical values into strings, then into files.
/// @param num 
void Manager::write(int num)
{
  std::string s = std::to_string(num);

  file << s;
};

// Unexpected behavior
/*
void Manager::is_complete(bool completed)
{
  if(debugging)
  {
    std::cout << db_string << "Checking if program termination was nominal..." << "\n";
  }

  const char *str = file_name.c_str();

  std::cout << "CMakeEasy is now checking for incomplete CMakeLists.txt files." << "\n";

  if(completed)
  {
    std::cout << "CMakeLists.txt\n";
    std::cout << "was determined as finished, no action was taken." << "\n";
  }
  else
  {
    std::cout << "Running delete function with sudo permissions..." << "\n";

    system("sudo rm " + *str);

    std::cout << "Process complete." << "\n";
  }
}
*/