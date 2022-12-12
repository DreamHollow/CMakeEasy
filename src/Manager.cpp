#include "Manager.hpp"

Manager::Manager()
{
  this->init_vars();
  this->init_file();
};

Manager::~Manager()
{
  this->file.close();
  // Invoke file being moved to new folder
  // this->move_file();
};

void Manager::init_vars()
{
  this->debug = true;
};

/// @brief The file is initialized early into the program, along with the directory.
void Manager::init_file()
{
  /*
  if(OS_WINDOWS) // Any Windows
  {
    system("mkdir Created_Lists");
  }
  else if(!OS_WINDOWS) // Linux
  {
    system("mkdir Created_Lists");
  }
  */

  // This catch-all should really be left in for worst-case file writing scenarios.

  if(!this->file.is_open())
  {
    try
    {
      std::cout << "Initializing file settings..." << "\n";

      file.open(file_name.c_str(), std::ios::out | std::ios::app);

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

// Writes char arrays and strings.
void Manager::write(std::string context)
{
  file << context;
};

// Writes int values as strings.
void Manager::write(int num)
{
  std::string s = std::to_string(num);

  file << s;
};

/*
void Manager::move_file()
{
  // Function designed to avoid overwriting existing files.

  if(OS_WINDOWS)
  {
    system("move -y 'CMakeLists.txt' 'Created_Lists'"); // Ask for permission
  }
  else if(!OS_WINDOWS)
  {
    system("mv -n 'CMakeLists.txt' 'Created_Lists'"); // No Clobber
  }
};
*/