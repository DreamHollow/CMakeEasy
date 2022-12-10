#ifndef ALTSTRING_HPP
#define ALTSTRING_HPP
#include <iostream>
#include <string>

/// @brief Reduces some output clutter and allows for unique input from user.
class AltString
{
public:
    AltString();
    virtual ~AltString();

    // Public Functions - Explainers
    void start();
    void minor_vers();
    void release_vers();
    void program_vers();
    void program_lang();
    void package();
    void op_sys();
    void standard();
    void source();

    // Entry Detection
    int entry_fail(bool is_array);

private:
    // Variables
    bool is_command;
    // char store[32];

    // Init
    void init_vars();

};

#endif