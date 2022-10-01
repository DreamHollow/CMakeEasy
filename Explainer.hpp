#ifndef EXPLAINER_HPP
#define EXPLAINER_HPP
#include <iostream>
#include <string>

// This class contains pre-written explanations
// This way it clutters up the main program much less

class Explainer
{
public:
    Explainer();
    virtual ~Explainer();

    // Public Functions
    void start();
    void standard();
    int entry_fail();

private:
    // Variables

    // Functions

};

#endif