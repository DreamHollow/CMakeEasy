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
  std::string f_slash = "/";

  if(!OS_WINDOWS) // Linux
  {
    // This should be the working $HOME directory
    file_name = homedir + f_slash + file_name;

    file_dir = file_name;
  }
  else
  {
    // There are few easier ways to do this on Windows
    system("mkdir Lists");
    homedir = "Lists/CMakeLists.txt";
    file_name = homedir;

    file_dir = file_name;
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
        std::cout << "Warning: If CMakeLists.txt exists in /src folder," << "\n";
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

/*
void Manager::read(std::string file_location)
{
  std::string file_path;
  std::ifstream in_file;

  if(OS_WINDOWS) // Alter for Windows
  {
    // TO-DO
    // file_path = "C:/Program Files (x86)/CMakeEasy/plaintext";
    // file_path = file_path + "/" + file_location;
  }
  else // Alter for Linux
  {
    file_path = "/opt/cmakeeasy";
    file_path = file_path + "/" + file_location;
  }

  try
  {
    in_file.open(file_path);

    if(in_file.fail())
    {
      std::cout << "ERROR:\n";
      std::cout << "Explanation text failed to load. Unable to continue operation." << "\n";

      // Removed call to 'free()'
      // May cause system lockup
      // Just let it unroll

      throw "Unable to load text file.";
    }
    else // If file success, read the file
    {
      std::string stream;

      if(in_file.is_open())
      {
        while(in_file.good())
        {
          in_file >> stream;

          std::cout << stream;
        }
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what();
  }

  in_file.close();
}
*/