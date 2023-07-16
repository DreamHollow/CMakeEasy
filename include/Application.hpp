#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "AltString.hpp"

class Application
{
public:
    Application();
    virtual ~Application();

    const bool running() const { return this->is_active; };

    void run();

private:
    // Variables
    bool is_active;
    bool valid_standard;
    bool has_package;
    bool more_files;
    // bool comment;

    //short major = 0;
    //short minor = 0;
    //short release = 0;

    //short standard = 0;
    short actual = 0;

    // short package_vers = 0;

    // Integer used to avoid problematic char-style input.
    // short yes_no = 0;

    const std::string linebreak = "------------";

    // std::string project_name;
    // std::string exe_name;

    std::string package_name;
    // std::string library_segment;
    // std::string library_vis; // Library visibility

    std::string class_name;
    std::string source{ "src/" };

    std::string declaration;
    std::string requirement;
    // std::string flag;
    // std::string parameter;

    std::vector<std::string> packages;

    // Functions
    void early_setup();
    void package_setup();
    void standard_setup();
    void source_and_includes();
    void package_loop();
    void entry_check();
    void verbose_output();
    void finish_touches();
    void lin_flags();
    // void win_flags();
    void generate_final();
    // void move_file();

    // Input
    short input_val(short& num);
    int input_val(int& num);
    float input_val(float& num);
    std::string input_string(std::string& str);
    std::string input_longstring(std::string& str);

    // Output
    // void set_string(std::string& str);

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