#include "Manager.hpp"

Manager::Manager()
{
  this->init_vars();
  this->init_file();
};

Manager::~Manager()
{
  this->file.close();
};

void Manager::init_vars()
{
  debugging = false;
  this->yes_no = 0;
};

/// @brief The file is initialized early into the program, along with the directory.
void Manager::init_file()
{
  // This catch-all should really be left in for worst-case file writing scenarios.

  if(!this->file.is_open())
  {
    try
    {
      std::cout << "\n";
      std::cout << "Warning: If CMakeListst.txt exists in /src folder," << "\n";
      std::cout << "it will be overwritten!" << "\n";
      std::cout << "\n";
      std::cout << "Please remove any CMakeList.txt files that you" << "\n";
      std::cout << "Do not wish to lose." << "\n";
      std::cout << "\n";
      std::cout << "Initializing file settings..." << "\n";

      if(debugging)
      {
      }

      file.open(file_name.c_str(), std::ios::out | std::ios::trunc);

      if(file.fail())
      {
        std::cout << "The CMakeLists.txt file could not be edited." << "\n";
        std::cout << "An error occurred: 'Bad CMakeLists argument'." << "\n";
        
        throw "Bad CMakeLists directory argument.";
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }

    if(file.good())
    {
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