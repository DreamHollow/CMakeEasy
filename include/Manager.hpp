#ifndef MANAGER_HPP_INCLUDED
#define MANAGER_HPP_INCLUDED 1
#include <string>
#include <fstream>
#include "Globals.h"

// Homedir is used and recycled for initialization
// But this part only takes over for a Windows system
#if OS_WIN
static std::string homedir = "";
#endif

/// @brief File manager. Designed to input or output file data
/// as needed, usually through simple read-write directives.
class Manager
{
public:
  Manager(std::string target_file, bool read_only);
  ~Manager();

  // Public Variables
  std::string file_dir;

  // Public Const Declarations
  const std::string name() const { return this->file_name; };

  // Public Functions
  void write(std::string context);
  void write(int num);
  const std::string read();
  void mark_to_delete();

private:
  // Variables
  bool read_only;
  bool already_read;
  bool liquidate;
  
  std::string list_dir;
  std::string file_name;

  // Memory
  void free_data();

  // Objects
  std::ifstream infile; // Read-Only
  std::ofstream outfile; // Write-Only
};

#endif
