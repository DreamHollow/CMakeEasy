#include "Manager.hpp"

Manager::Manager()
{

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
      system("mkdir Lists");
      homedir = "Lists/CMakeLists.txt";
      file_dir = file_name;
    }
    else // Linux
    {
      file_name = homedir + f_slash + file_name;
    }
  }

  // Read-only

  try
  {
    if(read_only == true)
    {
      if(!infile.is_open())
      {
        std::cout << db_msg("\n");
        std::cout << db_msg("Current file path: ");
        std::cout << db_msg(file_name);
        std::cout << db_msg("\n");
        std::cout << db_msg("Attempting to open read-only file...");

        infile.open(file_name.c_str());

        if(infile.fail())
        {
          std::cout << db_msg("\n");
          std::cout << db_msg("File opening failed.\n");
          std::cout << db_msg("Could not open: ");
          std::cout << db_msg(file_name);
          std::cout << db_msg("\n");

          free_data();

          throw "Unable to open read-only file!";
        }
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what();
  }
  
  std::cout << db_msg("\n");
  std::cout << db_msg("File name for instance: ");
  std::cout << db_msg(file_name);
  std::cout << db_msg("\n");

  // Read-write

  if(!read_only)
  {
    std::cout << db_msg("Read-only flag set to false, initializing CMakeLists.txt...\n");

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

        // Flags a boolean fail -- moves program to application, then main
        if(outfile.fail())
        {
          std::cout << "ERROR: CMakeLists.txt file is unable to be opened.\n";
          std::cout << "CMakeEasy cannot continue.\n";
          std::cout << "\n";

          free_data();

          throw "Unable to open file.";
        }
      }
      else
      {
        std::cout << "CMakeLists.txt file is valid, allowing edits.\n";

        std::cout << db_msg("\n");
        std::cout << db_msg(file_name);
        std::cout << db_msg("\n");
        std::cout << db_msg("is ready to be modified.\n");
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  // End of file check
};

Manager::~Manager()
{
  std::cout << db_msg("Manager deconstructed...\n");

  free_data();
};

/// @brief Forces file to close to prevent leaks.
/// Outputs for debugger.
void Manager::free_data()
{
  if(infile.is_open())
  {
    this->infile.close();

    std::cout << db_msg("Manager: Closed a read-only file.\n");
  }
  else
  {
    std::cout << db_msg("Manager: No read-only file to close.\n");
  }

  if(outfile.is_open())
  {
    this->outfile.close();

    std::cout << db_msg("Manager: Closed an output file.\n");
  }
  else
  {
    std::cout << db_msg("Manager: No output file to close.\n");
  }
}

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