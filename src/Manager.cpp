#include "Manager.hpp"

Manager::Manager()
{
  //this->init_vars();
  //this->init_file();
};

Manager::Manager(std::string target_file, bool read_only)
{
  this->file_name = target_file;
  this->read_only = read_only;

  std::string f_slash = "/";

  if(!this->read_only)
  {
    if(OS_WINDOWS)
    {
      //std::string list_dir = "Lists";

      system("mkdir Lists");
      homedir = "Lists/CMakeLists.txt";
      file_dir = file_name;
    }
    else // Linux
    {
      file_name = homedir + f_slash + file_name;
    }
  }

  std::cout << db_msg("\n");
  std::cout << db_msg("File name for instance: ");
  std::cout << db_msg(file_name);
  std::cout << db_msg("\n");

  // Initialize file with same settings
  init_file();
};

Manager::~Manager()
{
  std::cout << db_msg("Manager deconstructed...\n");

  free();
};

/// @brief Forces file to close to prevent leaks.
/// Outputs for debugger.
void Manager::free()
{
  if(infile.is_open())
  {
    this->infile.close();

    std::cout << db_msg("Manager closed a read-only file.\n");
  }

  if(outfile.is_open())
  {
    this->outfile.close();

    std::cout << db_msg("Manager closed an output file.\n");
  }
}

/// @brief The file is initialized early into the program, along with the directory.
void Manager::init_file()
{
  // Initialize an AltString file
  if(this->read_only == true)
  {
    std::cout << db_msg("\n");
    std::cout << db_msg("Read-only function currently undefined.\n");
    std::cout << db_msg("\n");
  }
  else
  {
    std::cout << db_msg("\n");
    std::cout << db_msg("Read-only flag set to false, initializing CMakeLists.txt...\n");
    std::cout << db_msg("\n");

    try
    {
      if(!outfile.is_open())
      {
        std::cout << db_msg("\n");
        std::cout << db_msg("Current file path: ");
        std::cout << db_msg(file_name);
        std::cout << db_msg("\n");
        std::cout << db_msg("Attempting to create/edit CMakeLists.txt...\n");

        outfile.open(file_name.c_str(), std::ios::out | std::ios::trunc);

        if(outfile.fail())
        {
          std::cout << "ERROR: CMakeLists.txt file is unable to be opened.\n";
          std::cout << "CMakeEasy cannot continue.\n";

          free();

          throw "Unusuable file path.";
        }
        else // File is good
        {
          std::cout << "CMakeLists.txt file is valid, allowing edits.\n";

          std::cout << db_msg("\n");
          std::cout << db_msg(file_name);
          std::cout << db_msg("\n");
          std::cout << db_msg("is ready to be modified.\n");
        }
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  // This catch-all should really be left in for worst-case file writing scenarios.
  // If the CMakeLists.txt file cannot be accessed, it should not be written to!
};

/// @brief Writes char arrays and strings into files.
/// @param context 
void Manager::write(std::string context)
{
  outfile << context;
};

/// @brief Converts numerical values into strings, then into files.
/// @param num 
void Manager::write(int num)
{
  std::string s = std::to_string(num);

  outfile << s;
};