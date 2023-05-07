#include "Application.hpp"
// #include "CMakeEasyConfig.h"

// Needs C style arguments for Versioning to work.
int main(int argc, char* argv[])
{
    // Heap allocated both classes to prevent overflow of stack.

    Application app;

    while(app.running())
    {
        app.run();
    }

    return 0;
};