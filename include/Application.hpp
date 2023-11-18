#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED 1
#include "AltString.hpp"
#include <algorithm>
#ifdef _WIN32
#include <WinBase.h>
#endif

enum TEXT_FILES { START = 0, MINOR_V_TXT, RELEASE_TXT, PROGRAM_V_TXT, PROG_LANG_TXT,
    COMPONENT_TXT, OP_TXT, VERB_TXT, PACK_SET, INCLUDE_TXT, PACKAGES_TXT,
    STANDARDS_TXT, SOURCES_TXT, MORE_LIBS_TXT, PROMOTE_TXT };

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
    //bool more_files;

    short package_counter = 0;

    short actual = 0;

    const char exit_command[6] = "!exit";
    const std::string linebreak = "------------";

    std::string package_name;

    std::string declaration;
    std::string requirement;

    std::vector<std::string> packages;

    // Functions
    void early_setup();
    void package_setup();
    void standard_setup();
    void source_and_includes();
    void package_loop();
    int entry_check(int& value);
    short entry_check(short& value);
    float entry_check(float& value);
    std::string entry_check(std::string& str);
    void verbose_output();
    void finish_touches();
    void sys_flags();
    void flag_setting(int decision, bool is_windows);
    void generate_final();

    // Input
    short input_val(short& num);
    int input_val(int& num);
    float input_val(float& num);
    //auto input_val(auto& num);
    std::string input_string(std::string& str);
    std::string input_longstring(std::string& str);

    // Init
    void init_vars();
    void init_components();
    std::string init_directory(std::string file_dir, std::string file);
    void init_filetype(std::string file_name, bool read_only);

    // Memory
    void free_data();

    // Objects
    std::unique_ptr<AltString> alt;
    std::unique_ptr<Manager> ext_file;
    std::vector<std::shared_ptr<Manager>> text_files;
};

#endif
