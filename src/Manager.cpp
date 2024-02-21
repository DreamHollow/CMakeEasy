#include "Manager.hpp"

/// @brief Constructor initializing a file, then determining write status.
/// @param target_file 
/// @param read_only 
Manager::Manager(std::string target_file, bool read_only)
{
  this->file_name = target_file;
  this->read_only = read_only;
  this->liquidate = false;

  std::string f_slash = "/";

  if(!this->read_only)
  {
    if(OS_WIN)
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
  else
  {
    already_read = false;
  }

  // Read-only

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
        if(debug)
        {
          std::cout << (file_name);
        }
        std::cout << db_msg("\n");

        std::cout << "\n";
        std::cout << "ERROR: CMakeEasy failed to read a vital text file.\n";
        std::cout << "Program execution cannot continue.\n";
        std::cout << "Stopping CMakeEasy...\n";

        free_data();

        throw std::runtime_error("MANAGER::INFILE::LOAD_FAIL"); //"Unable to open read-only file!";
      }
      else
      {
        std::cout << db_msg("\n");
        std::cout << db_msg("Read-only file was opened successfully: ");
        std::cout << db_msg(file_name);
        std::cout << db_msg("\n");
      }
    }
  }
  
  std::cout << db_msg("\n");
  std::cout << db_msg("File name for instance: ");
  std::cout << db_msg(file_name);
  std::cout << db_msg("\n");

  // Read-write

  if(!read_only)
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
        std::cout << "\n";
        std::cout << "ERROR: CMakeLists.txt file is unable to be opened.\n";
        std::cout << "CMakeEasy cannot continue.\n";
        std::cout << "\n";

        free_data();

        throw std::runtime_error("MANAGER::OUTFILE::LOAD_FAIL"); //"Unable to open file.";
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
  }
};

Manager::~Manager()
{
  std::cout << db_msg("Manager deconstructing...\n");

  free_data();

  if(liquidate && !outfile.is_open())
  {
    std::cout << db_msg("File was set to be liquidated by Manager:\n");
    std::cout << db_msg(this->file_name);
    std::cout << db_msg("\n");
    std::cout << db_msg("Known file path: \n");
    std::cout << db_msg(file_name);
    std::cout << db_msg("\n");

    std::remove(file_name.c_str());

    std::cout << db_msg("File removed.\n");
  }
  else
  {
    if(!read_only)
    {
      std::cout << db_msg("No files were liquidated.\n");
    }
  }
};

/// @brief Forces file to close to prevent leaks.
/// Outputs for debugger.
void Manager::free_data()
{
  if(read_only)
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
  }
  else
  {
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

const std::string Manager::read()
{
  std::string str;

  // Resets the text file.
  // This prevents text events from displaying nothing.
  if(already_read)
  {
    infile.close();

    infile.open(file_name);
  }

  if(infile && infile.is_open())
  {
    std::ostringstream ss;
    ss << infile.rdbuf();
    str = ss.str();
  }

  already_read = true;

  return str;
}

void Manager::mark_to_delete()
{
  liquidate = true;

  std::cout << db_msg("File marked for deletion.\n");

  std::cout << "CMakeLists.txt will be deleted on program exit.\n";
  std::cout << "\n";
}