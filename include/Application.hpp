#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "AltString.hpp"
#include <algorithm>

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

    short actual = 0;

    const std::string linebreak = "------------";

    std::string package_name;

    std::string class_name;
    std::string source{ "src/" };

    std::string declaration;
    std::string requirement;

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
    void sys_flags();
    void flag_setting(int decision, bool is_windows);
    void generate_final();

    // Input
    short input_val(short& num);
    int input_val(int& num);
    float input_val(float& num);
    std::string input_string(std::string& str);
    std::string input_longstring(std::string& str);

    // Output

    // Init
    void init_vars();
    void init_components();
    void init_filetype(std::string file_name, bool read_only);

    // Memory
    void free_data();

    // Objects
    std::unique_ptr<AltString> text;
    std::unique_ptr<Manager> ext_file;
    std::vector<std::shared_ptr<Manager>> text_files;
};

#endif