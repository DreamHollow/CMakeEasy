#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "Manager.hpp"

class Application
{
public:
    Application();
    virtual ~Application();

    enum STATUS { SUCCESS = 0, FAILURE, CRITICAL_FAILURE };

    const bool running() const { return this->is_active; };

    void run();

private:
    // Variables
    int exit = 0;

    bool is_active;
    bool debugging;
    bool valid_standard;
    bool has_package;

    short major = 0;
    short minor = 0;
    short release = 0;

    short standard = 0;

    short package_vers = 0;

    // Integer used to avoid problematic char-style input.
    short yes_no = 0;

    char project_name[32];
    char exe_name[32];

    std::string package_name;
    std::string library_segment;
    std::string library_vis; // Library visibility

    std::string declaration;
    std::string requirement;

    std::vector<std::string> packages;

    // Functions
    void entry_check();

    // Init
    void init_vars();
    void init_components();

    // Memory
    void free();

    // Objects
    std::unique_ptr<AltString> text;
    std::unique_ptr<Manager> ext_file;
};

#endif