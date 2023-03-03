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
#include <iostream>
#include <vector>
#include "Globals.h"
#if OS_WINDOWS == 0
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

/// @brief File manager. Designed to input or output file data
/// as needed, usually through simple read-write directives.
class Manager
{
public:
  Manager();
  virtual ~Manager();

  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;

  // Public Const Declarations
  const std::string name() const { return this->file_name; };

  // Public Functions
  void write(std::string context);
  void write(int num);
  // void move_file();
  // void is_complete(bool completed);

private:
  // Variables
  int yes_no;
  std::string file_dir;

  // Constants
  std::string file_name = "/CMakeLists.txt";

  // Init
  void init_vars();
  void init_file();

  // Memory
  void free();

  // Objects
  std::ofstream file; // Write-Only
};

#endif
