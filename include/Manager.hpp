#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <stdio.h>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <iostream>
#include <vector>
#include "Globals.h"

#ifdef __unix__ // Linux
#define OS_WINDOWS 0
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
static struct passwd *pw = getpwuid(getuid());
static const char *homedir = pw->pw_dir;
#endif

#ifdef _WIN32
#define OS_WINDOWS 1
#include <windows.h>
std::string homedir = "";
#endif

#ifdef _WIN64
#define OS_WINDOWS 1
#include <windows.h>
std::string homedir = "";
#endif

/// @brief File manager. Designed to input or output file data
/// as needed, usually through simple read-write directives.
class Manager
{
public:
  Manager();
  virtual ~Manager();

  // Public Variables
  std::string file_dir;

  // Public Const Declarations
  const std::string name() const { return this->file_name; };

  // Public Functions
  void write(std::string context);
  void write(int num);

private:
  // Variables
  int yes_no;
  
  std::string file_name = "CMakeLists.txt"; // Slash direction depends on OS

  // Init
  void init_vars();
  void init_directives(int direct);
  void init_file();

  // Memory
  void free();

  // Objects
  std::ofstream file; // Write-Only
};

#endif
