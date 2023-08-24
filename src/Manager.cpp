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
  if(file_initialized(read_only))
  {
    std::cout << file_name + " initialized with no problems.\n";
  }
  else
  {
    std::cout << file_name + " failed to initialize.\n";
  }
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
  else
  {
    std::cout << db_msg("Manager wanted to close a read-only file, there was nothing.\n");
  }

  if(outfile.is_open())
  {
    this->outfile.close();

    std::cout << db_msg("Manager closed an output file.\n");
  }
  else
  {
    std::cout << db_msg("Manager wanted to close an output file, there was nothing.\n");
  }
}

/// @brief The file is initialized early into the program, along with the directory.
bool Manager::file_initialized(bool &ro)
{
  if(ro == true) // AltString
  {
    std::cout << db_msg("Read-only function currently undefined.\n");
  }
  else // CMakeLists
  {
    std::cout << db_msg("Read-only flag set to false, initializing CMakeLists.txt...\n");

    if(!outfile.is_open())
    {
      std::cout << db_msg("\n");
      std::cout << db_msg("Current file path: ");
      std::cout << db_msg(file_name);
      std::cout << db_msg("\n");
      std::cout << db_msg("Attempting to create/edit CMakeLists.txt...\n");

      outfile.open(file_name.c_str(), std::ios::out | std::ios::trunc);

      // Flags a boolean fail -- moves program to application, then main
      if(outfile.fail())
      {
        std::cout << "ERROR: CMakeLists.txt file is unable to be opened.\n";
        std::cout << "CMakeEasy cannot continue.\n";
        std::cout << "\n";

        free();

        return false;
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

  return true;
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