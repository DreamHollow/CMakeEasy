#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <fstream>
#include "Explainer.hpp"

/// @brief File manager. Designed to input or output file data
/// as needed, usually through simple read-write directives.

class Manager
{
public:
  Manager();
  virtual ~Manager();

  // Public Const Declarations
  const std::string name() const { return this->file_name; };
  const bool is_debugging() const { return this->debug; };

  // Public Functions
  void write(std::string context);
  void write(int num); // Overload

private:
  // Variables
  bool debug;

  // Constants
  const std::string file_name = "CMakeLists.txt";

  // Functions
  void init_file();

  // Objects
  std::ofstream file; // Write-Only
};

#endif
