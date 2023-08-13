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

  std::cout << db_msg("Manager closed the open file.\n");
}

void Manager::init_vars()
{
  this->yes_no = 0;
};

/// @brief The file is initialized early into the program, along with the directory.
void Manager::init_file()
{
  std::string f_slash = "/";

  if(!OS_WINDOWS) // Linux
  {
    // This should be the working $HOME directory

    file_name = homedir + f_slash + file_name; // Linux Home

    file_dir = file_name; // ~/home
  }
  else
  {
    // There are few easier ways to do this on Windows
    system("mkdir Lists");
    homedir = "Lists/CMakeLists.txt";
    file_name = homedir;

    file_dir = file_name; // Program Files
  }

  // This catch-all should really be left in for worst-case file writing scenarios.
  // If the CMakeLists.txt file cannot be accessed, it should not be written to!

  if(!this->file.is_open())
  {
    try
    {
      std::cout << db_msg("\n");
      std::cout << db_msg("Warning: If CMakeLists.txt exists in /src folder,\n");
      std::cout << db_msg("it will be overwritten!\n");

      if(OS_WINDOWS)
      {
        std::cout << "\n";
        std::cout << "Windows system detected." << "\n";
        std::cout << "\n";
        std::cout << "CMakeEasy will automatically write your CMakeLists.txt\n";
        std::cout << " to a sub-folder called 'Lists'." << "\n";
      }
      else
      {
        std::cout << "\n";
        std::cout << "Non-Windows system detected. Linux system assumed." << "\n";
        std::cout << "\n";
        std::cout << "CMakeEasy will automatically write your CMakeLists.txt\n";
        std::cout << "to your home directory folder." << "\n";
      }

      std::cout << "\n";
      std::cout << "Please remove any CMakeList.txt files that you" << "\n";
      std::cout << "Do not wish to lose." << "\n";
      std::cout << "\n";
      std::cout << "------" << "\n";
      std::cout << "\n";
      std::cout << "Initializing file settings..." << "\n";

      std::cout << db_msg("Current file path:\n");
      std::cout << db_msg(file_name);
      std::cout << db_msg("\n");
      std::cout << db_msg("Program attempting to open file 'CMakeLists'...\n");

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
      std::cout << db_msg("CMakeLists.txt is good, allowing edits.\n");

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