#include "Application.hpp"

int main()
{
    Application app;

    while(app.running())
    {
        app.run();
    }

    return 0;
};