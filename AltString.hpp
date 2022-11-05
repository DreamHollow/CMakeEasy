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
    void standard();
    void source();

    // Entry Detection
    int entry_fail();
    // int array_fail(int length, int max);
    // void string_entry(std::string s_input);

private:
    // Variables
    bool is_command;

    // Init
    void init_vars();

};

#endif