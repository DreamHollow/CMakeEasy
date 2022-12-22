#ifndef MANAGER_HPP
#define MANAGER_HPP

#ifdef __unix__
#define OS_WINDOWS 0
#elif defined(_WIN32)
#define OS_WINDOWS 1
#include <windows.h>
#elif defined(_WIN64)
#define OS_WINDOWS 1
#endif

#include <stdio.h>
#include <fstream>
#include <filesystem>
#include <cstring>
#include "AltString.hpp"

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
  void write(int num);
  // void move_file();

private:
  // Variables
  bool debug;
  int yes_no;

  // Constants
  const std::string db_string = "DEBUG - MANAGER: ";
  const std::string file_name = "CMakeLists.txt";

  // Functions
  void init_vars();
  void init_file();

  // Objects
  std::ofstream file; // Write-Only
};

#endif
