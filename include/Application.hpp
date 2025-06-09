#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED 1
#include "AltString.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#ifdef _WIN64
#include <WinBase.h>
#endif

enum TEXT_FILES { START = 0, MINOR_V_TXT, RELEASE_TXT, PROGRAM_V_TXT, PROG_LANG_TXT,
    COMPONENT_TXT, OP_TXT, VERB_TXT, PACK_SET, INCLUDE_TXT, PACKAGES_TXT,
    STANDARDS_TXT, SOURCES_TXT, MORE_LIBS_TXT, PROMOTE_TXT, LIB_SHORT };

class Application
{
public:
    Application();
    ~Application();

    bool running = false;

    //const bool running() const { return this->is_active; };

    void run();

private:
    // Variables
    bool valid_standard;
    bool has_package;

    short package_counter = 0;

    short actual = 0;

    const char exit_command[6] = "!exit";
    const std::string linebreak = "------------";

    std::string package_name;

    std::string declaration;
    std::string requirement;

    std::vector<std::string> packages;
    std::vector<std::string> dir_array;

    // Functions
    void early_setup();
    void package_setup();
    void standard_setup();
    void source_and_includes();
    void package_loop();
    std::string entry_check(std::string& str);
    void verbose_output();
    void finish_touches();
    void sys_flags();
    void flag_setting(int decision, bool is_windows);
    void set_windows_flags();
    void set_linux_flags();
    void generate_final();
    bool set_install_config();
    void config_text(const bool is_installed);
    void flag_instruction(const int choice, const bool windows);
    bool allow_runtime(std::string& string);
    void stop_and_remove(bool start_process);

    // Templates - Input
    template <typename InputVector> InputVector input_val(InputVector& num);
    template <typename InputData> InputData entry_check(InputData& value);

    // Input
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

template <typename InputVector>
inline InputVector Application::input_val(InputVector &num)
{
    std::cin >> num;

    return entry_check(num);
}

template <typename InputData>
inline InputData Application::entry_check(InputData &value)
{
    try
    {
        if(std::cin.fail())
        {
            std::cout << "\n";
            std::cout << "-- ERROR: INVALID INPUT --" << "\n";
            std::cout << "\n";

            std::cout << "Sorry, the program encountered an error." << "\n";
            std::cout << "This error message is encountered if input was considered unsafe" << "\n";
            std::cout << "for the program to process." << "\n";
            std::cout << "\n";
            std::cout << "If you don't understand why you have this error," << "\n";
            std::cout << "please raise an issue on the Github repository." << "\n";
            std::cout << "\n";
            std::cout << "Thank you." << "\n";
            std::cout << "\n";

            this->free_data();

            throw "Invalid data input!";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what();
    }

    return InputData();
}
