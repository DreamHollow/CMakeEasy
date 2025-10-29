#include "Application.hpp"
#include <filesystem>
#include <algorithm>

Application::Application()
{
    this->init_vars();
    this->init_components();
}

/// @brief Releases vectors, allows smart pointers to remove themselves.
Application::~Application()
{
    packages.clear();
    packages.shrink_to_fit();

    text_files.clear();
    text_files.shrink_to_fit();
}

void Application::init_vars()
{
    // Do not alter debugging state except in Globals.h

    // Start the pointers at null for safety reasons
    
    running = true; // Starts runtime
    alt = nullptr;
    ext_file = nullptr;

    valid_standard = false;
    has_package = false;
}

std::string Application::init_directory(std::string file_dir, std::string file)
{
    return (file_dir + file);
}

void Application::init_components()
{
    bool installed = false;
    alt = std::make_unique<AltString>();
    ext_file = std::make_unique<Manager>("CMakeLists.txt", false);
    std::string system_path;
    std::string debug_dir;

    installed = set_install_config();

    // Directory vector appends known system files
    // It's up to the installation state which set are actually used.

    dir_array.push_back("start.txt"); // 0
    dir_array.push_back("minor_vers.txt"); // 1
    dir_array.push_back("release_vers.txt"); // 2
    dir_array.push_back("program_vers.txt"); // 3
    dir_array.push_back("program_lang.txt"); // 4
    dir_array.push_back("component_entry.txt"); // 5
    dir_array.push_back("op_sys.txt"); // 6
    dir_array.push_back("verbose.txt"); // 7
    dir_array.push_back("package_setup_text.txt"); // 8
    dir_array.push_back("include_dirs.txt"); // 9
    dir_array.push_back("package.txt"); // 10
    dir_array.push_back("standard.txt"); // 11
    dir_array.push_back("source.txt"); // 12
    dir_array.push_back("more_libs.txt"); // 13
    dir_array.push_back("promote.txt"); // 14
    dir_array.push_back("library_shorthand.txt");

    config_text(installed);

    if(!installed)
    {
        // Windows and Linux handle this differently
        #ifdef _WIN32
        std::filesystem::path cwd = std::filesystem::current_path();
        system_path = cwd.string();
        #endif

        #ifdef __linux__
        system_path = std::filesystem::current_path();
        #endif

        std::string file_location;

        debug_dir = (system_path + "/" + "text/");

        std::cout << db_msg("\n");
        std::cout << db_msg("Current debug directory: " + debug_dir);
        std::cout << db_msg("\n");
        std::cout << db_msg("Performing debug file checks...\n");

        for(auto it : dir_array)
        {
            file_location = init_directory(debug_dir, it);
            init_filetype(file_location, true);

            std::cout << db_msg("Last item appended: " + file_location);
            std::cout << db_msg("\n");
        }
    }

    dir_array.clear();
    dir_array.shrink_to_fit();
}

/// @brief Adds individual text files to a vector for later iteration.
/// @param file_name 
/// @param read_only 
void Application::init_filetype(std::string file_name, bool read_only)
{
    std::shared_ptr<Manager> file_ptr = std::make_unique<Manager>(file_name, read_only);
    text_files.push_back(file_ptr);

    std::cout << db_msg("File added to vector: ");
    std::cout << db_msg(file_name);
    std::cout << db_msg("\n");
}

/// @brief Absolute call to free memory. Used during exceptions and forced exits.
void Application::free_data()
{
    packages.clear();
    packages.shrink_to_fit();

    if(alt == nullptr)
    {
        std::cout << db_msg("AltString was NULL, releasing...\n");

        alt.release();
    }
    else
    {
        alt.reset();
    }

    if(ext_file == nullptr)
    {
        std::cout << db_msg("Manager was NULL, releasing...\n");

        ext_file.release();
    }
    else
    {
        ext_file.reset();
    }

    text_files.clear();
    text_files.shrink_to_fit();

    std::cout << db_msg("'alt' and 'ext_file' pointers released safely.\n");
}

const std::string Application::entry_check(std::string *str)
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

        throw std::runtime_error("APPLICATION::ENTRY_CHECK::INVALID_INPUT");
    }

    return *str;
}

void Application::early_setup()
{
    short major = 0;
    short minor = 0;
    short release = 0;

    std::string project_name;

    std::cout << "Your version: ";
    input_val<short>(major);
    std::cout << "\n";

    // Version numbering (CMake)

    std::cout << text_files.at(MINOR_V_TXT)->read();
    std::cout << "\n";

    std::cout << "Your version: ";
    input_val<short>(minor);
    std::cout << "\n";

    std::cout << text_files.at(RELEASE_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "Your version: ";
    input_val<short>(release);
    std::cout << "\n";

    // This is for CMake versioning, not program versioning.

    std::cout << "\n";
    std::cout << "Configuring line inputs..." << "\n";
    std::cout << "You have designated your version of CMake as ";
    std::cout << major << "." << minor << "." << release << "\n";
    std::cout << "\n";
    std::cout << "Please keep in mind that if this is wrong," << "\n";
    std::cout << "you will have to start this process over." << "\n";

    // Start writing data to CMakeLists.txt

    std::cout << "\n";
    std::cout << "Saving " << ext_file->name() << " to your current directory..." << "\n";

    ext_file->write(alt->declare(CMAKE_MIN)); // cmake_minimum
    ext_file->write("(");
    ext_file->write(alt->declare(VERS_NUM)); // VERSION
    ext_file->write(" ");
    ext_file->write(major);
    ext_file->write(".");
    ext_file->write(minor);
    ext_file->write(".");
    ext_file->write(release);
    ext_file->write(")");
    ext_file->write("\n");

    if(debug)
    {
        std::cout << "DEBUG STATEMENT:\n";
        std::cout << "\n";
        std::cout << "Line in CMakeLists should read as\n";
        std::cout << "'cmake_minimum_required(VERSION";
        std::cout << " " << major << "." << minor << "." << release << ")" << "'";
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "END DEBUG STATEMENT\n";
        std::cout << "\n";
    }

    std::cout << "Wrote " << "'" << alt->declare(CMAKE_MIN) << "'" << " line automatically." << "\n";
    std::cout << "\n";

    std::cout << "\n";
    std::cout << "Please enter the name of the project that you are trying to create." << "\n";
    std::cout << "\n";
    std::cout << "Type '!exit' if you want to stop CMakeEasy.\n";
    std::cout << "\n";
    std::cout << "Your project name: ";
    input_string(&project_name);
    std::cout << "\n";

    std::cout << "\n";
    std::cout << "Your project's name has been evaluated as '" << project_name << "'" << '\n';
    std::cout << "and will be saved as such." << "\n";
    std::cout << "\n";

    ext_file->write(alt->declare(PROJ));
    ext_file->write("(");
    ext_file->write(project_name);
    std::cout << "\n";

    major = 0;
    minor = 0;
    release = 0;

    std::cout << text_files.at(PROGRAM_V_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";
    
    std::cout << "Your choice: ";
    input_val<short>(yes_no);
    std::cout << "\n";

    std::cout << "\n";

    switch(yes_no)
    {
        case 1:
        std::cout << "Please enter the major version number for your program." << "\n";
        std::cout << "Example: [1].0.0" << "\n";
        std::cout << "Your version: ";
        input_val<short>(major);

        std::cout << "Please enter the minor version number for your program." << "\n";
        std::cout << "Example: 1.[0].0" << "\n";
        std::cout << "Your version: ";
        input_val<short>(minor);

        std::cout << "Please enter the release version number for your program." << "\n";
        std::cout << "Example: 1.0.[0]" << "\n";
        std::cout << "Your version: ";
        input_val<short>(release);

        ext_file->write(" ");
        ext_file->write(alt->declare(VERS_NUM));
        ext_file->write(" ");
        ext_file->write(major);
        ext_file->write(".");
        ext_file->write(minor);
        ext_file->write(".");
        ext_file->write(release);

        std::cout << "\n";
        break;

        case 2:
        std::cout << "Understood. No version number will be added to your program build at this time." << "\n";
        std::cout << "\n";

        break;
        
        default:
        std::cout << "Sorry, that is not a valid list choice." << "\n";
        std::cout << "Defaulting to choice 2, no program version will be added." << "\n";
        std::cout << "\n";
        break;
    }

    yes_no = 0; // Reset the variable

    // Declaring Program Language Format

    std::cout << "\n";
    std::cout << text_files.at(PROG_LANG_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";

    ext_file->write(" ");
    ext_file->write(alt->declare(PROGRAM_LANG));
    ext_file->write(")");
    ext_file->write("\n");

    if(debug)
    {
        std::cout << "DEBUG STATEMENT:\n";
        std::cout << "\n";
        std::cout << "Line should read as: " << "\n";
        std::cout << alt->declare(PROJ) << "(" << project_name << " ";

        if(major && minor != 0)
        {
            std::cout << alt->declare(VERS_NUM) << " " << major << "." << minor << "." << release;
        }

        std::cout << " ";
        std::cout << alt->declare(PROGRAM_LANG);
        std::cout << ")";
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "END DEBUG STATEMENT\n";
        std::cout << "\n";
    }
}

void Application::package_setup()
{
    // Package insertion loop continues in case of multiple packages
    // This can be a little confusing and will need to be reworked - TODO

    // Package loop cannot be exited with !exit in the same way other loops can

    do
    {
        std::cout << text_files.at(PACKAGES_TXT)->read();
        std::cout << "\n";
        std::cout << "\n";

        short package_vers = 0;

        text_files.at(PACK_SET)->read();
        std::cout << "\n";
        std::cout << "\n";

        std::cout << "Your package: ";
        input_string(&package_name);
        std::cout << "\n";

        if(package_name == "!none")
        {
            std::cout << "\n";
            std::cout << "Understood, no more packages will be added." << "\n";
            std::cout << "\n";
        }
        else
        {
            packages.push_back(package_name); // Keep a list

            std::cout << "\n";
            std::cout << "Are there any details to add to this package?" << "\n";
            std::cout << "For example, version number, etc." << "\n";
            std::cout << "If there is a version number, enter it here by adding a number." << "\n";
            std::cout << "If not, just type 0 instead." << "\n";
            std::cout << "\n";
            std::cout << "Your package version number: ";
            input_val<short>(package_vers);
            std::cout << "\n";

            yes_no = 0; // reset

            std::cout << "\n";
            std::cout << "Should this package be required to be found by CMake?" << "\n";
            std::cout << "This is important, to help CMake determine which packages are optional\n";
            std::cout << "installs, and which packages are mandatory for the program to work." << "\n";
            std::cout << "\n";
            std::cout << "Set package as required?" << "\n";
            std::cout << "1 for yes, 2 for no." << "\n";
            std::cout << "\n";
            std::cout << "Your choice: ";
            input_val<short>(yes_no);
            std::cout << "\n";

            bool req_package = false;

            switch(yes_no)
            {
                case 1:
                {
                    req_package = true;

                    std::cout << "Understood, the package will be flagged as required." << "\n";
                    break;
                }
                case 2:
                {
                    std::cout << "Understood, the package will be flagged as optional." << "\n";
                    break;
                }
                default:
                {
                    std::cout << "Unrecognized choice. Setting 'required' setting to off." << "\n";
                    break;
                }
            }

            // Ask for components that WILL be used.

            bool entries = false;
            std::string co_entry;
            std::vector<std::string> co_entries;

            while(co_entry != "!none")
            {
                std::cout << "\n";
                std::cout << "Please enter library components, if applicable." << "\n";
                std::cout << "Because of how CMake works, these components must be provided" << "\n";
                std::cout << "in two different places." << "\n";
                std::cout << "\n";
                std::cout << "Example: 'SFML 2 REQUIRED COMPONENTS graphics'" << "\n";
                std::cout << "This can vary between libraries when it comes to CMake." << "\n";
                std::cout << "\n";
                std::cout << "If you don't need to add any components, enter '!none' instead." << "\n";
                std::cout << "\n";
                std::cout << "Your next component: ";
                input_string(&co_entry);
                std::cout << "\n";

                if(co_entry == "!none")
                {
                    break;
                }
                else
                {
                    entries = true;
                    co_entries.push_back(co_entry);
                }
            }

            std::cout << db_msg("\n");
            std::cout << db_msg(package_name);
            std::cout << db_msg("\n");
            std::cout << db_msg("was added to 'packages' vector.\n");
            std::cout << db_msg("\n");

            ext_file->write(alt->declare(FIND_PACKAGE)); // find_package
            ext_file->write("(");
            ext_file->write(package_name);

            // If package version is relevant
            if(package_vers != 0)
            {
                ext_file->write(" ");
                ext_file->write(package_vers);
            }

            if(req_package)
            {
                ext_file->write(" ");
                ext_file->write(alt->declare(REQ));
            }

            if(entries)
            {
                ext_file->write(" ");
                ext_file->write("COMPONENTS");
            }

            for(auto it : co_entries)
            {
                ext_file->write(" ");
                ext_file->write(it); // Write the current value
            }

            ext_file->write(")");

            has_package = true;

            co_entries.clear();
            co_entries.shrink_to_fit();
        }

        ext_file->write("\n");

    }while(package_name != "!none");

    package_name.clear();
}

/// @brief Writes C++ standards to document based on input.
void Application::standard_setup()
{
    // bool valid_standard = false;
    short standard = 0;

    std::cout << "Your standard: ";
    std::cin.clear();
    input_val<short>(standard);
    std::cout << "\n";

    std::cout << "\n";

    actual = 0;

    switch(standard)
    {
        case 0:
        {
            valid_standard = false;

            std::cout << "This is not a valid choice." << "\n";
            std::cout << "Your standard will be configured to the default." << "\n";
            standard = 4;

            std::cout << db_msg("\n");
            std::cout << db_msg("DEBUG:");
            std::cout << db_msg("'standard' was assigned to the number 4.\n");
            std::cout << db_msg("\n");

            break;
        }
        case 1:
        {
            valid_standard = true;
            actual = 23;

            std::cout << "Configuring file for C++23 standards..." << "\n";
            declaration = alt->declare(CMAKE_STANDARD);
            declaration.append(" " + std::to_string(actual));
            break;
        }
        case 2:
        {
            valid_standard = true;
            actual = 20;

            std::cout << "Configuring file for C++20 standards..." << "\n";
            declaration = alt->declare(CMAKE_STANDARD);
            declaration.append(" " + std::to_string(actual));
            break;
        }
        case 3:
        {
            valid_standard = true;
            actual = 17;

            std::cout << "Configuring file for C++17 standards..." << "\n";
            declaration = alt->declare(CMAKE_STANDARD);
            declaration.append(" " + std::to_string(actual));
            break;
        }
        case 4:
        {
            valid_standard = false;

            std::cout << "Standards not set; default C++ standards will be implemented." << "\n";
            break;
        }
        default:
        {
            valid_standard = false;

            std::cout << "The provided input is not part of the existing list." << "\n";
            std::cout << "Standards not set; default C++ standards will be implemented." << "\n";
            break;
        }
    }

    if(valid_standard)
    {
        requirement = alt->declare(CMAKE_REQ);
        requirement.append(" ON");

        ext_file->write(alt->declare(SET_DATA)); // set
        ext_file->write("(");
        ext_file->write(declaration);
        ext_file->write(")");
        ext_file->write("\n");
        ext_file->write(alt->declare(SET_DATA));
        ext_file->write("(");
        ext_file->write(requirement);
        ext_file->write(")\n");
        ext_file->write("\n"); // Make some extra space
    }
    else
    {
        ext_file->write("\n");
    }

    if(debug)
    {
        if(valid_standard)
        {
            std::cout << "\n";
            std::cout << "DEBUG DATA:" << "\n";
            std::cout << "Line in file should read as" << "\n";
            std::cout << alt->declare(SET_DATA) << "(" << declaration << ")'" << "\n";
            std::cout << "'" << requirement << "'" << "\n";
            std::cout << "\n";
        }
        else
        {
            std::cout << "\n";
            std::cout << "DEBUG DATA:" << "\n";
            std::cout << "Declaration was either invalid or not assigned." << "\n";
        }
    }
}

/// @brief The look where package components are linked to libraries.
void Application::package_loop()
{
    bool more_libraries;

    if(has_package)
    {
        std::cout << "Packages were entered previously:" << "\n";
        std::cout << "\n";

        // Show previously entered packages.

        for(auto it : packages)
        {
            std::cout << it << "\n";
        }

        if(package_counter > 0)
        {
            std::cout << "\n";
            std::cout << "Package data for " << packages.at(package_counter - 1);
            std::cout << " already parsed.\n";

            if(package_counter < 2)
            {
                std::cout << "ERROR: ";
                std::cout << "New package data cannot be entered for less than 2 packages!\n";
                std::cout << "CMakeEasy cannot continue.\n";
                std::cout << "\n";

                throw std::runtime_error("APPLICATION::PACKAGE_LOOP::INVALID_COUNTER");
            }
            
            std::cout << "Please parse data for: " << packages.at(package_counter) << "\n";
            std::cout << "\n";
        }

        std::cout << "\n";
        std::cout << "Please only enter components for packages" << "\n";
        std::cout << "that were not previously entered." << "\n";
        std::cout << "\n";

        // Text file not loading in properly on loop-thru - TODO

        std::cout << text_files.at(COMPONENT_TXT)->read();
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "Your choice: ";

        input_val<short>(yes_no);
        std::cout << "\n";

        std::string library_segment;
        std::string library_shorthand;

        switch(yes_no)
        {
            case 1:
            {
                ext_file->write("\n"); // Force newline

                std::cout << text_files.at(LIB_SHORT)->read();
                std::cout << " "; 
                input_string(&library_shorthand);
                std::cout << "\n";

                library_shorthand.append("-"); // Append a dash

                // Ask about PUBLIC, PRIVATE, INTERFACE - TODO
                // Automatically infers PRIVATE for now

                do
                {
                    std::cout << "\n";
                    std::cout << "Your current library prefix: " << library_shorthand << "\n";
                    std::cout << "\n";
                    std::cout << "Please link library components." << "\n";
                    std::cout << "Library components can be linked with a dash, but one will be provided for you." << "\n";
                    std::cout << "\n";
                    std::cout << "If you have no library components to link, please enter '!none' and your" << "\n";
                    std::cout << "unused entry will be excluded from the CMakeLists.txt file.";
                    std::cout << "\n";
                    std::cout << "Please enter any additional library components. (example: sfml-graphics)" << "\n";
                    std::cout << "\n";
                    std::cout << "Your next library target: ";

                    input_string(&library_segment);

                    if(library_segment == "!none") // Stop the process
                    {
                        std::cout << "\n";
                        std::cout << "No additional library files will be targeted." << "\n";
                        std::cout << "\n";

                        library_shorthand.clear();
                        library_segment.clear();

                        more_libraries = false;
                    }
                    else
                    {
                        more_libraries = true;
                    }

                    if(library_shorthand.empty()) // No library to link
                    {
                        std::cout << "\n";
                        std::cout << "No new library information was entered.\n";
                        std::cout << "Skipping...\n";
                        std::cout << "\n";
                    }
                    else
                    {
                        ext_file->write(alt->declare(TARGET_LINK_LIB)); // target_link_libraries
                        ext_file->write("(");
                        ext_file->write(alt->declare(PROJECT_NAME));
                        ext_file->write(" ");
                        ext_file->write(alt->declare(PRIV)); // Make this modifiable - TODO
                        ext_file->write(" ");
                        ext_file->write(library_shorthand);
                        ext_file->write(library_segment); // library-component
                        ext_file->write(")");
                    }

                    library_segment.erase();

                    ext_file->write("\n"); // New line for new target
                }while(more_libraries);

                package_counter += 1;

                if(debug)
                {
                    std::cout << db_string << "Package counter increased to ";
                    std::cout << package_counter << "\n";
                    std::cout << "\n";
                }

                break; // Still part of case 1
            }
            case 2:
            {
                if(has_package)
                {
                    std::cout << "Please understand that some packages will not work" << "\n";
                    std::cout << "without relevant components. If your package does not" << "\n";
                    std::cout << "function, it maybe missing critical files from CMakeLists.txt!" << "\n";
                }
                std::cout << "\n";
                std::cout << "No more library components will be added." << "\n";
                std::cout << "\n";
                break;
            }
            default:
            {
                std::cout << "\n";
                std::cout << "This selection is invalid." << "\n";
                std::cout << "Defaulting to selection 2: No." << "\n";
                std::cout << "\n";
                break;
            }
        }
    }
    else
    {
        std::cout << "\n";
        std::cout << "No package or library data entered. Moving on..." << "\n";
        std::cout << "\n";
    }

    if(debug)
    {
        std::cout << db_msg("Package loop exited here.\n");
    }

    yes_no = 0;
}

/// @brief Defines program compilation, sourcing, and include folders.
void Application::source_and_includes()
{
    std::string exe_name;
    bool more_files = false;
    std::string class_name;
    std::string source = "src/";

    std::cout << "Please enter the name of your main executable, along with .cpp: ";
    input_string(&exe_name);
    std::cout << "\n";

    ext_file->write(alt->declare(ADD_EXEC)); // add exe
    ext_file->write("(");
    ext_file->write(alt->declare(PROJECT_NAME));
    ext_file->write(" ");
    ext_file->write(source);
    ext_file->write(exe_name); // should appear as src/(exe_name)

    std::cout << "If your program is using classes, please add your class files." << "\n";
    std::cout << "The program will loop entry until you specify that you are done." << "\n";
    std::cout << "\n";

    //more_files = false;

    do
    {
        std::cout << "If you have no additional files to include, please enter '!none' instead." << "\n";
        std::cout << "\n";
        std::cout << "Please enter any additional class names. (example: Class.cpp)" << "\n";
        std::cout << "Your next class file: ";

        // Input class name
        input_string(&class_name);

        if(class_name == "!none")
        {
            std::cout << "\n";
            std::cout << "No additional class names will be added." << "\n";
            std::cout << "\n";

            class_name.clear();
            source.clear();

            more_files = false;
        }
        else
        {
            more_files = true;

            if(debug)
            {
                std::cout << "\n";
                std::cout << "DEBUG STATEMENT:\n";
                std::cout << "Last written class information was\n";
                std::cout << alt->declare(ADD_EXEC);
                std::cout << "(";
                std::cout << alt->declare(PROJECT_NAME) << " ";
                std::cout << source;
                std::cout << exe_name;
                std::cout << "\n";
            }
        }

        if(more_files) // If source and class are empty, writes empty space.
        {
            ext_file->write("\n");
        }
        ext_file->write(source);
        ext_file->write(class_name);

        if(debug)
        {
            std::cout << source;
            std::cout << class_name;
            std::cout << "\n";
            std::cout << "END DEBUG STATEMENT.\n";
            std::cout << "\n";
        }

    }while(more_files);

    ext_file->write(")\n");
}

void Application::flag_setting(int decision, bool is_windows)
{
    std::cout << "\n";

    flag_instruction(decision, is_windows);

    db_msg("\n");
    db_msg("Ending flag setting routine...\n");
}

/// @brief Main run loop for CMakeEasy, defines all function entry points.
void Application::run()
{
    std::cout << db_msg("\n");
    std::cout << db_msg("Trying to read file at position 0...\n");
    std::cout << db_msg("\n");

    std::cout << text_files.at(START)->read();
    std::cout << "\n";
    std::cout << "\n";

    // functions that don't start with 'text' should be left alone.

    early_setup();

    std::cout << linebreak << "\n";
    std::cout << "\n";

    package_setup();

    std::cout << linebreak << "\n";
    std::cout << "\n";

    std::cout << text_files.at(STANDARDS_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";
    
    standard_setup();

    std::cout << "\n";
    std::cout << linebreak << "\n";
    std::cout << "\n";

    verbose_output();

    std::cout << "\n";

    std::cout << text_files.at(SOURCES_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";

    // Source Setup

    std::cout << "\n";
    std::cout << linebreak << "\n";
    std::cout << "\n";

    // Ask user for any additional directories or included files - TODO

    std::cout << text_files.at(INCLUDE_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "\n";
    std::cout << "\n";

    source_and_includes();

    std::cout << linebreak << "\n";
    std::cout << "\n";

    yes_no = 0;

    PACK_LOOP: // Used goto so function doesn't need more declarations

    // Packages / Libraries only
    package_loop();

    std::cout << "\n";
    std::cout << text_files.at(MORE_LIBS_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Your choice: ";

    input_val<short>(yes_no);

    // Must be outside a function
    switch(yes_no)
    {
        case 1:
        {
            std::cout << "Understood." << "\n";
            std::cout << "Looping back to library linking." << "\n";
            std::cout << "\n";
            goto PACK_LOOP; // goto is actually easier here than other options

            break;
        }
        case 2:
        {
            std::cout << "Understood." << "\n";
            std::cout << "No more library links will be added." << "\n";
            std::cout << "\n";

            break;
        }
        default:
        {
            std::cout << "\n";
            std::cout << "Sorry, this is not a valid choice." << "\n";
            std::cout << "Defaulting to 2: No." << "\n";
            std::cout << "\n";

            break;
        }
    }

    std::cout << linebreak << "\n";
    std::cout << "\n";

    finish_touches();

    std::cout << text_files.at(PROMOTE_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Your choice: ";

    // Convert into function.

    generate_final();

    std::cout << "\n";
    std::cout << linebreak << "\n";
    std::cout << "\n";

    // Memory will free automatically from here on.

    if(OS_WIN)
    {
        std::cout << "The process is finished.\n";
        std::cout << "\n";
        std::cout << "You can find your CMakeLists.txt file in\n";
        std::cout << "your 'cmakeeasy' directory under 'Lists'.\n";
    }
    else
    {
        std::cout << "The process is finished.\n";
        std::cout << "\n";
        std::cout << "You can find your CMakeLists.txt file in\n";
        std::cout << "your Linux home directory.\n";
    }

    std::cout << db_msg("\n");
    std::cout << db_msg("Files closed.\n");
    std::cout << db_msg("\n");
    std::cout << db_msg("Manager and AltString pointers released.");
    std::cout << db_msg("\n");
    std::cout << db_msg("Memory objects wiped.\n");
    std::cout << db_msg("\n");
    std::cout << db_msg("Reached end of program.\n");
    std::cout << db_msg("\n");

    running = false; // Terminate program
}


void Application::sys_flags()
{
    yes_no = 0;
    bool more_flags = false;
    std::string flag;
    std::string parameter;

    std::cout << "Would you like to set CMake instructions for Windows?\n";
    std::cout << "\n";
    std::cout << "If you choose yes, CMakeEasy will write out an instructional\n";
    std::cout << "set for Windows users to compile CMake programs with.\n";
    std::cout << "\n";
    std::cout << "This will make it possible to add crucial Windows-specific\n";
    std::cout << "instructions.\n";
    std::cout << "\n";
    std::cout << "1. Yes, I want to provide CMake with extra instruction.\n";
    std::cout << "2. No, I don't want to add any additional instructions.\n";
    std::cout << "\n";

    std::cout << "Your choice: ";
    input_val<short>(yes_no);
    std::cout << "\n";

    flag_setting(yes_no, true);

    std::cout << "Would you like to set CMake instructions for Linux?\n";
    std::cout << "\n";
    std::cout << "If you choose yes, CMakeEasy will write out an instructional\n";
    std::cout << "set for Linux users to compile with.\n";
    std::cout << "\n";
    std::cout << "This makes it possible to add crucial Linux-specific instructions.\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "1. Yes, I want to provide CMake with extra instruction.\n";
    std::cout << "2. No, I don't want to add any additional instructions.\n";
    std::cout << "\n";

    std::cout << "Your choice: ";
    input_val<short>(yes_no);
    std::cout << "\n";

    flag_setting(yes_no, false);
}

void Application::finish_touches()
{
    std::cout << db_msg("\n");
    std::cout << db_msg("Writing additional standards info...\n");
    std::cout << db_msg("\n");

    // Set standard include directory

    ext_file->write("\n");
    ext_file->write(alt->declare(INCLUDE_DIR));
    ext_file->write("(include)\n");
    //ext_file->write("\n");
    //ext_file->write("# Auto-generated comment:\n");
    //ext_file->write("# Post-compile data\n");
    ext_file->write("\n");

    // Recycle multiple input var here

    if(valid_standard)
    {
        ext_file->write(alt->declare(TARGET_COMPILE));
        ext_file->write("(");

        // Ask user about PRIVATE / PUBLIC / INTERFACE preference - TODO

        // Default this to PRIVATE for now
        ext_file->write(alt->declare(PROJECT_NAME));
        ext_file->write(" ");
        ext_file->write(alt->declare(PRIV));
        ext_file->write(" ");
        ext_file->write("cxx_std_");
        ext_file->write(actual);
        ext_file->write(")\n");
    }

    yes_no = 0;

    // std::cout << linebreak << "\n";

    std::cout << text_files.at(OP_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";

    std::cout << linebreak << "\n" << "\n";

    sys_flags();

    std::cout << linebreak << "\n" << "\n";

    yes_no = 0;
}

void Application::verbose_output()
{
    std::cout << db_msg("\n");
    std::cout << db_msg("Asking user about verbose CMake setting...\n");
    std::cout << db_msg("\n");

    std::cout << text_files.at(VERB_TXT)->read();
    std::cout << "\n";
    std::cout << "\n";

    yes_no = 0;

    std::cout << "\n";
    std::cout << "Your choice: ";
    input_val<short>(yes_no);

    switch(yes_no)
    {
        case 1:
        {
            std::cout << "Committing changes to CMakeLists.txt file..." << "\n";
            std::cout << "\n";
            ext_file->write(alt->declare(SET_DATA)); // set
            ext_file->write("(");
            ext_file->write(alt->declare(VERBOSE_MAKE));
            ext_file->write(" ");
            ext_file->write("true");
            ext_file->write(")");
            ext_file->write("\n");
            ext_file->write("\n");

            if(debug)
            {
                std::cout << "DEBUG DATA:\n";
                std::cout << "Wrote the following to CMakeLists.txt:\n";
                std::cout << alt->declare(SET_DATA);
                std::cout << "(";
                std::cout << alt->declare(VERBOSE_MAKE);
                std::cout << " true";
                std::cout << ")";
                std::cout << "\n";
            }

            break;
        }
        case 2:
        {
            std::cout << "Understood.\n";
            std::cout << "CMakeLists.txt will not have a 'verbose' configuration." << "\n";
            break;
        }
        default:
        {
            std::cout << "This was not a valid input. Assuming 'no'." << "\n";
            break;
        }
    }
}

void Application::generate_final()
{
    bool comment = false;
    yes_no = 0;

    input_val<short>(yes_no);

    // Hopefully this fixes weird bug where comment is always added
    switch(yes_no)
    {
        case 1:
        comment = true;
        break;
        
        case 2:
        comment = false;
        break;

        default:
        std::cout << "Sorry, that is not a valid list choice." << "\n";
        std::cout << "Defaulting to 'no'." << "\n";
        comment = false;
        break;
    }

    if(comment)
    {
        std::cout << "Automatically generating comment..." << "\n";

        ext_file->write("\n");
        ext_file->write("# Auto-generated comment:\n");
        ext_file->write("# This list made with CMakeEasy.\n");

        std::cout << "\n";
        std::cout << "Comment was generated." << "\n";
    }
    else
    {
        std::cout << "\n";
        std::cout << "Comment will not be generated." << "\n";
    }
}

/// @brief Function checks if string input is valid. If it can't be, it halts operation.
/// @return str
std::string Application::input_string(std::string* str)
{
    // Please note that trying to enter nothing will result in
    // the program continuing to ask for data until something is
    // actually entered.
    
    std::cin >> *str;

    if(!allow_runtime(*str))
    {
        free_data();

        exit(0);
    }

    return entry_check(*str);
}

/// @brief Similar function to input_string but with less truncation.
/// @param str 
/// @return 
std::string Application::input_longstring(std::string* str)
{
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, *str);

    return entry_check(*str);
}

bool Application::set_install_config()
{
    bool install_state = false;

    // Instead of using the #define call
    // The OS_WIN flag helps determine if Windows or Linux

    // Detect installation type
    if(OS_WIN)
    {
        //bool installed;
        const char* win_dir = "C:/Program Files/cmakeeasy";

        if(std::filesystem::is_directory(win_dir))
        {
            std::cout << db_msg("\n");
            std::cout << db_msg("WINDOWS system\n");
            std::cout << db_msg("\n");
            std::cout << db_msg("CMakeEasy was found to be installed.\n");
            std::cout << db_msg("Installed files will be used.\n");
            std::cout << db_msg("\n");

            return true;
        }
        else
        {
            std::cout << db_msg("\n");
            std::cout << db_msg("WINDOWS system\n");
            std::cout << db_msg("\n");
            std::cout << db_msg("CMakeEasy 'text' directory not found,\n");
            std::cout << db_msg("assuming debug configuration.\n");
            std::cout << db_msg("\n");
        }
    }
    else // Linux
    {
        const char* unix_dir = "/usr/local/etc/cmakeeasy";

        if(std::filesystem::is_directory(unix_dir))
        {
            std::cout << db_msg("\n");
            std::cout << db_msg("UNIX system\n");
            std::cout << db_msg("\n");
            std::cout << db_msg("CMakeEasy was found to be installed.\n");
            std::cout << db_msg("Installed files will be used.\n");
            std::cout << db_msg("\n");

            return true;
        }
        else
        {
            std::cout << db_msg("\n");
            std::cout << db_msg("UNIX system\n");
            std::cout << db_msg("\n");
            std::cout << db_msg("CMakeEasy opt directory not found,\n");
            std::cout << db_msg("assuming debug configuration.\n");
            std::cout << db_msg("\n");
        }
    }

    return false;
}

/// @brief Checks if a text directory can be accessed,
/// then initializes files for program use.
void Application::config_text(const bool is_installed)
{
    if(is_installed && OS_WIN)
    {
        const std::string win_dir("C:/Program Files/cmakeeasy/text/");
        std::string file_location;

        for(auto it : dir_array)
        {
            // Very unlikely, but worth catching if it happens
            if(it.empty()) // A vector is missing and cannot be used
            {
                std::cout << "ERROR:\n";
                std::cout << "Some file data could not be initialized.\n";

                throw std::runtime_error("APPLICATION::CONFIG_TEXT::FILE_DATA_MISSING"); //"Missing file data!";
            }

            file_location = init_directory(win_dir, it);
            init_filetype(file_location, true);

            std::cout << db_msg("Last item appended: " + file_location);
            std::cout << db_msg("\n");
        }
    }
    else if(is_installed && !OS_WIN) // Text files for Linux system
    {
        const std::string directive{"/usr/local/etc/cmakeeasy/"};
        std::string file_location;

        for(auto it : dir_array)
        {
            if(it.empty())
            {
                std::cout << "ERROR:\n";
                std::cout << "Some file data could not be initialized.\n";

                throw std::runtime_error("APPLICATION::CONFIG_TEXT::FILE_DATA_MISSING"); //"Missing file data!";
            }

            file_location = init_directory(directive, it);
            init_filetype(file_location, true);

            std::cout << db_msg("Last item appended: " + file_location);
            std::cout << db_msg("\n");
        }
    }
}

void Application::flag_instruction(const int choice, const bool windows)
{

    if(windows)
    {
        std::cout << db_msg("\n");
        std::cout << db_msg("Beginning flag/instruction routine...\n");
        std::cout << db_msg("\n");

        switch(choice)
        {
            case 1: // Windows
            {
                set_windows_flags();

                break;
            }
            case 2:
            {
                std::cout << "Understood, no specific CMake instructions will be used\n";
                std::cout << "to compile for Windows systems.\n";
                break;
            }
            default:
            {
                std::cout << "This choice is not recognized.\n";
                std::cout << "Defaulting to option 2: no.\n";

                break;
            }
        }
    }

    if(!windows)
    {
        std::cout << db_msg("\n");
        std::cout << db_msg("Beginning flag/instruction routine...\n");
        std::cout << db_msg("\n");

        switch(choice)
        {
            case 1:
            {
                set_linux_flags();

                break;
            }
            case 2:
            {
                std::cout << "Understood, no specific CMake instructions will be used\n";
                std::cout << "to compile for Linux systems.\n";
                break;
            }
            default:
            {
                std::cout << "This choice is not recognized.\n";
                std::cout << "Defaulting to option 2: no.\n";

                break;
            }
        }
    }
}

void Application::set_windows_flags()
{
    bool more_flags = false;
    std::string current;
    std::string str_context;
    std::string permissions;
    yes_no = 0;

    more_flags = true;
    std::cout << "------\n";
    std::cout << "WINDOWS SETTINGS\n";
    std::cout << "------\n";
    std::cout << "\n";
    std::cout << "Adding Windows-specific instructions will require\n";
    std::cout << "more data. A list of common operating system specific\n";
    std::cout << "commands will be provided.\n";
    std::cout << "\n";

    ext_file->write("\n");
    ext_file->write("if(WIN32)");
    ext_file->write("\n");
    std::cout << "\n";

    while(more_flags)
    {
        std::cout << "Recognized instructions:\n";
        alt->show_commands();
        std::cout << "\n";

        std::cout << "\n";
        std::cout << "Which instruction would you like to add?\n";
        std::cout << "Type !none if you want to stop adding instructions.\n";
        std::cout << "\n";
        std::cout << "Your instruction: ";
        input_string(&current);

        std::cout << "\n";

        if(current == "!none")
        {
            std::cout << "\n";
            std::cout << "Understood, halting process.\n";
            std::cout << "\n";

            more_flags = false;
        }
        else // Add an indent for nesting
        {
            ext_file->write("   ");
        }

        // To prevent user error it checks the given command
        if(std::find(alt->commands.begin(),alt->commands.end(), current) != alt->commands.end())
        {
            db_msg("\n");
            db_msg("Command found in vector, proceeding...\n");
            db_msg("\n");

            if(current == "install")
            {
                std::cout << "\n";
                std::cout << "You will be asked to clarify install permissions for the system.\n";
                std::cout << "\n";
            }

            std::cout << "What is the context of this instruction " << "'" << current << "'" << "?\n";
            std::cout << "Parenthesis will be added automatically.\n";
            std::cout << "Example: message(STATUS This is a status message.)\n";
            std::cout << current << "(";
            input_longstring(&str_context);

            if(current == "install")
            {
                std::cout << "What are the install permissions for this instruction?\n";
                std::cout << "Examples: OWNER_EXECUTE, GROUP_EXECUTE (etc.)";
                std::cout << "PERMISSIONS ";
                input_string(&permissions);
                std::cout << "\n";
            }

            db_msg("\n");
            db_msg("Writing...\n");
            db_msg("\n");

            ext_file->write(current);
            ext_file->write("(");
            ext_file->write(str_context);

            if(current == "install")
            {
                ext_file->write(" PERMISSIONS ");
                ext_file->write(permissions);
            }

            ext_file->write(")");
            ext_file->write("\n");

            if(debug)
            {
                std::cout << "DEBUG STATEMENT:\n";
                std::cout << "Latest lines written are\n";
                std::cout << current << "(" << str_context;
                    if(current == "install")
                    {
                        std::cout << " PERMISSIONS ";
                        std::cout << permissions;
                    }

                std::cout << ")";
                std::cout << "\n";
                std::cout << "END DEBUG STATEMENT\n";
            }
        }
        else // Do nothing for now
        {
            db_msg("\n");
            db_msg("Command not found in vector.\n");
            db_msg("\n");

            std::cout << "\n";
            std::cout << "This statement was not recognized by CMakeEasy.\n";
            std::cout << "\n";
        }
    }

    // Outside of instruction loop, so finish writing

    ext_file->write("endif()");
    ext_file->write("\n");
}

void Application::set_linux_flags()
{
    bool more_flags = false;
    std::string current;
    std::string str_context;
    std::string permissions;
    yes_no = 0;

    more_flags = true;
    std::cout << "------\n";
    std::cout << "LINUX SETTINGS\n";
    std::cout << "------\n";
    std::cout << "\n";
    std::cout << "Adding Windows-specific instructions will require\n";
    std::cout << "more data. A list of common operating system specific\n";
    std::cout << "commands will be provided.\n";
    std::cout << "\n";

    ext_file->write("\n");
    ext_file->write("if(UNIX)");
    ext_file->write("\n");
    std::cout << "\n";

    while(more_flags)
    {
        std::cout << "Recognized instructions:\n";
        alt->show_commands();
        std::cout << "\n";

        std::cout << "\n";
        std::cout << "Which instruction would you like to add?\n";
        std::cout << "Type !none if you want to stop adding instructions.\n";
        std::cout << "\n";
        std::cout << "Your instruction: ";
        input_string(&current);
        std::cout << "\n";

        if(current == "!none")
        {
            std::cout << "\n";
            std::cout << "Understood, halting process.\n";
            std::cout << "\n";

            more_flags = false;
        }
        else
        {
            ext_file->write("   ");
        }

        if(std::find(alt->commands.begin(),alt->commands.end(), current) != alt->commands.end())
        {
            db_msg("\n");
            db_msg("Command found in vector, proceeding...\n");
            db_msg("\n");

            /*
            if(current == "install")
            {
                std::cout << "\n";
                std::cout << "You will be asked to clarify install permissions for the system.\n";
                std::cout << "\n";
            }
            */

            std::cout << "What is the context of this instruction " << "'" << current << "'" << "?\n";
            std::cout << "Parenthesis will be added automatically.\n";
            std::cout << "Example: message(STATUS This is a status message.)\n";
            std::cout << current << "(";
            input_longstring(&str_context);

            /*
            if(current == "install")
            {
                std::cout << "What are the install permissions for this instruction?\n";
                std::cout << "Examples: OWNER_EXECUTE, GROUP_EXECUTE (etc.)";
                std::cout << "PERMISSIONS ";
                input_string(permissions);
                std::cout << "\n";
            }
            */

            db_msg("\n");
            db_msg("Writing...\n");
            db_msg("\n");

            ext_file->write(current);
            ext_file->write("(");
            ext_file->write(str_context);

            /*
            if(current == "install")
            {
                ext_file->write(" PERMISSIONS ");
                ext_file->write(permissions);
            }
            */

            ext_file->write(")");
            ext_file->write("\n");

            if(debug)
            {
                std::cout << "DEBUG STATEMENT:\n";
                std::cout << "Latest lines written are\n";
                std::cout << current << "(" << str_context;

                std::cout << ")";
                std::cout << "\n";
                std::cout << "END DEBUG STATEMENT\n";
            }
        }
        else // Do nothing for now
        {
            db_msg("\n");
            db_msg("Command not found in vector.\n");
            db_msg("\n");

            std::cout << "\n";
            std::cout << "This statement was not recognized by CMakeEasy.\n";
            std::cout << "\n";
        }
    }

    // Outside of instruction loop, so finish writing

    ext_file->write("endif()");
    ext_file->write("\n");
}

/// @brief Runtime checker. If relevant command is given, program must stop.
/// @param string 
/// @return 
bool Application::allow_runtime(std::string& string)
{
    if(string == "!exit")
    {
        short temp = 0;

        std::cout << "WARNING: Stopping CMakeEasy before completing the CMakeLists.txt\n";
        std::cout << "file will result in an incomplete and possibly inoperable file.\n";
        std::cout << "\n";
        std::cout << "Really quit CMakeEasy?\n";
        std::cout << "\n";
        std::cout << "1. Yes, and also delete the CMakeLists.txt file.\n";
        std::cout << "2. Yes, but keep the CMakeLists.txt file.\n";
        std::cout << "3. No, continue operation.\n";
        std::cout << "\n";
        std::cout << "Your choice: ";

        std::cin >> temp;
        entry_check(temp);

        switch(temp)
        {
            case 0:
            {
                std::cout << "ERROR: 0 is not a valid choice.\n";
                std::cout << "Exiting CMakeEasy without deleting anything...\n";

                stop_and_remove(false);

                return false;
            }
            case 1:
            {
                std::cout << "Understood.\n";
                std::cout << "CMakeEasy will stop running and delete it's generated file.\n";

                stop_and_remove(true);

                return false;
            }
            case 2:
            {
                std::cout << "Understood.\n";
                std::cout << "CMakeEasy will stop running, but keep the created file.\n";

                stop_and_remove(false);

                return false;
            }
            case 3:
            {
                std::cout << "Understood.\n";
                std::cout << "CMakeEasy will continue normally.\n";

                // Clean the string, it's useless as-is.

                string.clear();

                break;
            }
        }
    }

    return true;
}

/// @brief A normally silent process that just deletes a created CMake list if necessary.
/// @param start_process 
void Application::stop_and_remove(bool start_process)
{
    if(start_process)
    {
        std::cout << db_msg("stop_and_remove() starting...\n");
        std::cout << db_msg("Marking CMakeLists.txt for deletion...\n");

        ext_file->mark_to_delete();

        //db_msg("Forcing runtime to stop...");
        std::cout << db_msg("\n");
    }
    else // Debugging purposes
    {
        std::cout << db_msg("\n");
        std::cout << db_msg("stop_and_remove() was called,\n");
        std::cout << db_msg("stop_and_remove() exited without making changes.\n");
        std::cout << db_msg("\n");
    }
}
