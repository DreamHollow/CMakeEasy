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

    // Public Functions - Explainers
    void show_commands();

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