#ifndef ALTSTRING_HPP
#define ALTSTRING_HPP
#include "Manager.hpp"

/// @brief Reduces some output clutter and loosely handles inputs.
class AltString
{
public:
    AltString();
    virtual ~AltString();

    // Public Variables
    const std::string declare(int num);

    // Public Functions - Readers

    // Public Functions - Explainers
    //void package();
    //void more_libs();
    //void op_sys();
    void show_commands();
    //void standard();
    //void source();
    //void include_dirs();
    //void promote();
    //void verbose();

    // Public Vars
    std::vector<std::string> commands;

private:
    // Variables
    bool is_command;
    std::vector<std::string> declarations;

    // Init
    void init_vars();

    // Memory
    void free_data();
};

#endif