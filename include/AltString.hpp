#ifndef ALTSTRING_HPP
#define ALTSTRING_HPP
#include <iostream>
#include <string>
#include <vector>

/// @brief Reduces some output clutter and loosely handles inputs.
class AltString
{
public:
    AltString();
    virtual ~AltString();

    // Public Variables
    const std::string declare(int num);

    // Public Functions - Explainers
    void start();
    void minor_vers();
    void release_vers();
    void program_vers();
    void program_lang();
    void package();
    void component_entry();
    void more_libs();
    void op_sys();
    void standard();
    void source();
    void include_dirs();
    void promote();

    // Entry Detection
    // int entry_fail(bool is_array);

private:
    // Variables
    bool is_command;
    std::vector<std::string> declarations;

    // Init
    void init_vars();

};

#endif