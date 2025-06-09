#include "Application.hpp"
#include <iostream>

int main()
{
    Application app;

    try
    {
        while(app.running)
        {
            app.run();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
};