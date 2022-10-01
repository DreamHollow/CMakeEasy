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

  if(!this->file.is_open())
  {
    this->file.open(file_name);

    std::cout << "\n";
    std::cout << file_name << " is ready to be modified." << "\n";
    std::cout << "\n";
  }
};

void Manager::write(std::string context)
{
  file << context;
};

// For writing numbers to string
void Manager::write(int num)
{
  std::string s = std::to_string(num);

  file << s;
};