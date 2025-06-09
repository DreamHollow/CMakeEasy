#ifndef ALTSTRING_HPP_INCLUDED
#define ALTSTRING_HPP_INCLUDED 1
#include "Manager.hpp"
#include <vector>

enum DECLARATION { CMAKE_MIN = 0, PROJ, VERS_NUM, PROGRAM_LANG, CONF_FILE,
    TARGET_LINK_LIB, CMAKE_STANDARD, SET_DATA, ADD_EXEC, INCLUDE_DIR,
    TARGET_COMPILE, PROJECT_NAME, PUB, PRIV, INTERFACE, CMAKE_REQ,
    REQ, COMP, FIND_PACKAGE, VERBOSE_MAKE };

/// @brief Reduces some output clutter and loosely handles inputs.
class AltString
{
public:
    AltString();
    virtual ~AltString();

    // Public Variables
    const std::string declare(int num);

    // Public Functions - Explainers
    void show_commands();

    // Public Vars
    std::vector<std::string> commands;

private:
    // Variables
    std::vector<std::string> declarations;

    // Init
    void init_vars();

    // Memory
    void free_data();
};

#endif