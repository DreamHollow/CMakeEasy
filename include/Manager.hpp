#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <fstream>
#include <filesystem>
#include <cstring>
#include <iostream>
#include <vector>
#include "Globals.h"

// If a Windows system is being used
#if OS_WINDOWS
static std::string homedir = "";
#endif

/// @brief File manager. Designed to input or output file data
/// as needed, usually through simple read-write directives.
class Manager
{
public:
  Manager();
  Manager(std::string target_file, bool read_only);
  virtual ~Manager();

  // Public Variables
  std::string file_dir;

  // Public Const Declarations
  const std::string name() const { return this->file_name; };
  const bool readonly_open() const { return this->infile.is_open(); };
  const bool writefile_open() const { return this->outfile.is_open(); };

  // Public Functions
  void write(std::string context);
  void write(int num);

private:
  // Variables
  bool read_only;
  
  std::string list_dir;
  std::string file_name; // = "CMakeLists.txt";

  // Init
  void init_vars();
  bool file_initialized(bool &ro);

  // Memory
  void free();

  // Objects
  std::ifstream infile; // Read-Only
  std::ofstream outfile; // Write-Only
};

#endif
