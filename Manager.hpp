#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <fstream>
#include <iostream>
#include <string>

class Manager
{
public:
  Manager();
  virtual ~Manager();

  // Public Const Declarations
  const std::string name() const { return this->file_name; };

  // Public Functions
  void write(std::string context);
  void write(int num); // Overload

private:
  // Variables
  const std::string file_name = "CMakeLists.txt";

  // Functions
  void init_file();

  // Objects
  std::ofstream file; // Write-Only
};

#endif
