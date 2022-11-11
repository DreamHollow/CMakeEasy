#include "Manager.hpp"

Manager::Manager()
{
  this->init_file(); // This could probably be optimized
};

Manager::~Manager()
{
  this->file.close();
};

void Manager::init_file()
{
  this->debug = true;

  // This catch-all should really be left in for worst-case file writing scenarios.

  if(!this->file.is_open())
  {
    try
    {
      std::cout << "Initializing file settings..." << "\n";
      this->file.open(file_name);

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