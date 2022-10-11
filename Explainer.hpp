#ifndef EXPLAINER_HPP
#define EXPLAINER_HPP
#include <iostream>
#include <string>

/// @brief Simply outputs pre-formatted text to reduce clutter for
/// the overall program.
class Explainer
{
public:
    Explainer();
    virtual ~Explainer();

    // Public Functions
    void start();
    void minor_vers();
    void release_vers();
    void program_vers();
    void standard();
    void source();
    int entry_fail();

private:
    // Variables

    // Functions

};

#endif