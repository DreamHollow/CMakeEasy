#include "Application.hpp"

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

    is_active = true; // Starts runtime
    text = nullptr;
    ext_file = nullptr;

    valid_standard = false;
    has_package = false;
}

/// @brief Initializes smart pointers for AltString and Manager classes.
void Application::init_components()
{
    text = std::make_unique<AltString>();
    ext_file = std::make_unique<Manager>("CMakeLists.txt", false);
}

void Application::init_filetype(std::string file_name, bool read_only)
{
    std::shared_ptr<Manager> file_ptr = std::make_shared<Manager>(file_name, read_only);
    text_files.push_back(file_ptr);
}

/// @brief Absolute call to free memory. Used during exceptions.
void Application::free_data()
{
    packages.clear();
    packages.shrink_to_fit();

    if(text == nullptr)
    {

        std::cout << db_msg("AltString was NULL, releasing...\n");

        text.release();
    }
    else
    {
        text.reset();
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

    std::cout << db_msg("'text' and 'ext_file' pointers released safely.\n");
}

/// @brief Checks iostream input. It will force the program to stop
/// if the input fails or doesn't match the type.
void Application::entry_check()
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
}

void Application::early_setup()
{
    short major = 0;
    short minor = 0;
    short release = 0;

    std::string project_name;

    std::cout << "Your version: ";
    input_val(major);
    std::cout << "\n";

    // Version numbering (CMake)

    text->minor_vers();

    std::cout << "Your version: ";
    input_val(minor);
    std::cout << "\n";

    text->release_vers();

    std::cout << "Your version: ";
    input_val(release);
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

    ext_file->write(text->declare(0)); // cmake_minimum
    ext_file->write("(");
    ext_file->write(text->declare(2)); // VERSION
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

    std::cout << "Wrote " << "'" << text->declare(0) << "'" << " line automatically." << "\n";
    std::cout << "\n";

    std::cout << "\n";
    std::cout << "Please enter the name of the project that you are trying to create." << "\n";
    std::cout << "\n";
    std::cout << "The input will only handle up to 32 characters, please don't abuse it!" << "\n";
    std::cout << "\n";
    std::cout << "Your project name: ";
    input_string(project_name);
    std::cout << "\n";

    std::cout << "\n";
    std::cout << "Your project's name has been evaluated as '" << project_name << "'" << '\n';
    std::cout << "and will be saved as such." << "\n";
    std::cout << "\n";

    ext_file->write(text->declare(1));
    ext_file->write("(");
    ext_file->write(project_name);
    std::cout << "\n";

    major = 0;
    minor = 0;
    release = 0;

    text->program_vers();
    
    std::cout << "Your choice: ";
    input_val(yes_no);
    std::cout << "\n";

    std::cout << "\n";

    switch(yes_no)
    {
        case 1:
        std::cout << "Please enter the major version number for your program." << "\n";
        std::cout << "Example: [1].0.0" << "\n";
        std::cout << "Your version: ";
        input_val(major);

        std::cout << "Please enter the minor version number for your program." << "\n";
        std::cout << "Example: 1.[0].0" << "\n";
        std::cout << "Your version: ";
        input_val(minor);

        std::cout << "Please enter the release version number for your program." << "\n";
        std::cout << "Example: 1.0.[0]" << "\n";
        std::cout << "Your version: ";
        input_val(release);

        ext_file->write(" ");
        ext_file->write(text->declare(2));
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
    text->program_lang();

    ext_file->write(" ");
    ext_file->write(text->declare(3));
    ext_file->write(")");
    ext_file->write("\n");

    if(debug)
    {
        std::cout << "DEBUG STATEMENT:\n";
        std::cout << "\n";
        std::cout << "Line should read as: " << "\n";
        std::cout << text->declare(1) << "(" << project_name << " ";

        if(major && minor != 0)
        {
            std::cout << text->declare(2) << " " << major << "." << minor << "." << release;
        }

        std::cout << " ";
        std::cout << text->declare(3);
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

    do
    {
        short package_vers = 0;

        std::cout << "\n";
        std::cout << "Please enter any extra packages you would like to add." << "\n";
        std::cout << "\n";
        std::cout << "Please note that you can enter packages one after another, then you will\n";
        std::cout << "be asked to add the relevant components afterward." << "\n";
        std::cout << "\n";
        std::cout << "If you don't want to add any more packages, just type '!none' instead." << "\n";
        std::cout << "Your package: ";
        input_string(package_name);
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
            input_val(package_vers);
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
            input_val(yes_no);
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
                input_string(co_entry);
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

            ext_file->write(text->declare(19)); // find_package
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
                ext_file->write(text->declare(17));
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
    input_val(standard);
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
            declaration = text->declare(6);
            declaration.append(" " + std::to_string(actual));
            break;
        }
        case 2:
        {
            valid_standard = true;
            actual = 20;

            std::cout << "Configuring file for C++20 standards..." << "\n";
            declaration = text->declare(6);
            declaration.append(" " + std::to_string(actual));
            break;
        }
        case 3:
        {
            valid_standard = true;
            actual = 17;

            std::cout << "Configuring file for C++17 standards..." << "\n";
            declaration = text->declare(6);
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
        requirement = text->declare(16);
        requirement.append(" ON");

        ext_file->write(text->declare(7)); // set
        ext_file->write("(");
        ext_file->write(declaration);
        ext_file->write(")");
        ext_file->write("\n");
        ext_file->write(text->declare(7));
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
            std::cout << text->declare(7) << "(" << declaration << ")'" << "\n";
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
    if(has_package)
    {
        std::cout << "Packages were entered previously:" << "\n";
        std::cout << "\n";

        // Show previously entered packages.

        for(auto it : packages)
        {
            std::cout << it << "\n";
        }
        std::cout << "\n";
        std::cout << "Please only enter components for packages" << "\n";
        std::cout << "that were not previously entered." << "\n";
        std::cout << "\n";

        text->component_entry();

        input_val(yes_no);
        std::cout << "\n";

        std::string library_segment;
        std::string library_shorthand;

        switch(yes_no)
        {
            case 1:
            {
                ext_file->write("\n"); // Force newline

                std::cout << "Please enter the library shorthand." << "\n";
                std::cout << "\n";
                std::cout << "For example, SFML becomes sfml and links to a component." << "\n";
                std::cout << "e.g. sfml-graphics links the graphics module." << "\n";
                std::cout << "\n";
                std::cout << "Once the library shorthand is entered, it will be reused until the" << "\n";
                std::cout << "user tells the program to stop entering components." << "\n";
                std::cout << "\n";
                std::cout << "PLEASE NOTE:\n";
                std::cout << "You do not have to re-enter your library name." << "\n";
                std::cout << "The library name you are providing components for\n";
                std::cout << "Will be displayed before each iteration." << "\n";
                std::cout << "\n";
                std::cout << "Your library: ";
                input_string(library_shorthand);
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

                    input_string(library_segment);

                    if(library_segment == "!none") // Stop the process
                    {
                        std::cout << "\n";
                        std::cout << "No additional library files will be targeted." << "\n";
                        std::cout << "\n";

                        library_shorthand.clear();
                        library_segment.clear();

                        more_files = false;
                    }
                    else
                    {
                        more_files = true;
                    }

                    if(library_shorthand.empty()) // No library to link
                    {
                        // ext_file->write("\n");
                    }
                    else
                    {
                        ext_file->write(text->declare(9)); // target_link_libraries
                        ext_file->write("(");
                        ext_file->write(text->declare(12));
                        ext_file->write(" ");
                        ext_file->write(text->declare(14)); // Make this modifiable - TODO
                        ext_file->write(" ");
                        ext_file->write(library_shorthand);
                        ext_file->write(library_segment); // library-component
                        ext_file->write(")");
                    }

                    library_segment.erase();

                    ext_file->write("\n"); // New line for new target
                }while(more_files);

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
        std::cout << "No package or library data entered. Skipping..." << "\n";
        std::cout << "\n";
    }

    yes_no = 0;
}

/// @brief Defines program compilation, sourcing, and include folders.
void Application::source_and_includes()
{
    std::string exe_name;

    std::cout << "Please enter the name of your main executable, along with .cpp: ";
    input_string(exe_name);
    std::cout << "\n";

    ext_file->write(text->declare(8)); // add exe
    ext_file->write("(");
    ext_file->write(text->declare(12));
    ext_file->write(" ");
    ext_file->write(source);
    ext_file->write(exe_name); // should appear as src/(exe_name)

    std::cout << "If your program is using classes, please add your class files." << "\n";
    std::cout << "The program will loop entry until you specify that you are done." << "\n";
    std::cout << "\n";

    more_files = false;

    do
    {
        std::cout << "If you have no additional files to include, please enter '!none' instead." << "\n";
        std::cout << "\n";
        std::cout << "Please enter any additional class names. (example: Class.cpp)" << "\n";
        std::cout << "Your next class file: ";

        // Input class name
        input_string(class_name);

        if(class_name == "!none")
        {
            std::cout << "\n";
            std::cout << "No additional class names will be added." << "\n";
            std::cout << "\n";

            source.clear(); // Make this empty to prevent write errors
            class_name.clear();

            more_files = false;
        }
        else
        {
            more_files = true;
        }

        if(more_files)
        {
            ext_file->write("\n"); // Seperator
        }
        ext_file->write(source);
        ext_file->write(class_name);

        // source.erase();
        class_name.erase();

    }while(more_files);

    ext_file->write(")\n");
}

void Application::flag_setting(int decision, bool is_windows)
{
    std::cout << "\n";
    bool more_flags = false;
    std::string current;
    std::string str_context;
    std::string permissions;
    yes_no = 0;

    if(is_windows)
    {
        std::cout << db_msg("\n");
        std::cout << db_msg("Beginning flag/instruction routine...\n");
        std::cout << db_msg("\n");

        switch(decision)
        {
            case 1:
            {
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
                    text->show_commands();
                    std::cout << "\n";

                    std::cout << "\n";
                    std::cout << "Which instruction would you like to add?\n";
                    std::cout << "Type !none if you want to stop adding instructions.\n";
                    std::cout << "\n";
                    std::cout << "Your instruction: ";
                    input_string(current);
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
                    if(std::find(text->commands.begin(),text->commands.end(), current) != text->commands.end())
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
                        input_longstring(str_context);

                        if(current == "install")
                        {
                            std::cout << "What are the install permissions for this instruction?\n";
                            std::cout << "Examples: OWNER_EXECUTE, GROUP_EXECUTE (etc.)";
                            std::cout << "PERMISSIONS ";
                            input_string(permissions);
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
                    }
                }

                // Outside of instruction loop, so finish writing

                ext_file->write("endif()");
                ext_file->write("\n");

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

    if(!is_windows)
    {
        std::cout << db_msg("\n");
        std::cout << db_msg("Beginning flag/instruction routine...\n");
        std::cout << db_msg("\n");

        switch(decision)
        {
            case 1:
            {
                more_flags = true;

                std::cout << "------\n";
                std::cout << "LINUX SETTINGS\n";
                std::cout << "------\n";
                std::cout << "\n";
                std::cout << "Adding Linux-specific instructions will require\n";
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
                    text->show_commands();
                    std::cout << "\n";

                    std::cout << "\n";
                    std::cout << "Which instruction would you like to add?\n";
                    std::cout << "Type !none if you want to stop adding instructions.\n";
                    std::cout << "\n";
                    std::cout << "Your instruction: ";
                    input_string(current);
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

                    // To prevent user error it checks the given command
                    if(std::find(text->commands.begin(),text->commands.end(), current) != text->commands.end())
                    {
                        db_msg("\n");
                        db_msg("Command found in vector, proceeding...\n");
                        db_msg("\n");

                        std::cout << "What is the context of this instruction " << "'" << current << "'" << "?\n";
                        std::cout << "Example: message(STATUS This is a status message.)\n";
                        std::cout << current << "(";
                        input_longstring(str_context);
                        std::cout << ")\n";

                        db_msg("\n");
                        db_msg("Writing...\n");
                        db_msg("\n");

                        ext_file->write(current);
                        ext_file->write("(");
                        ext_file->write(str_context);
                        ext_file->write(")");
                        ext_file->write("\n");

                        if(debug)
                        {
                            std::cout << "DEBUG STATEMENT:\n";
                            std::cout << "Latest lines written are\n";
                            std::cout << current << "(" << str_context << ")\n";
                            std::cout << "END DEBUG STATEMENT\n";
                        }
                    }
                    else // Do nothing for now
                    {
                        db_msg("\n");
                        db_msg("Command not found in vector.\n");
                        db_msg("\n");
                    }
                }

                // Finish and write

                ext_file->write("endif()");
                ext_file->write("\n");

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

    db_msg("\n");
    db_msg("Ending flag setting routine...\n");
}

/// @brief Main run loop for CMakeEasy, defines all function entry points.
void Application::run()
{
    // text->select_dir();

    // Select directory

    // Check for "files open" flags at very beginning
    // If nothing works, throw an exception
    // Don't show anything if there are no problems
    
    try
    {
        if(!ext_file->writefile_open())
        {
            std::cout << "\n";
            std::cout << "There was a serious error with CMakeLists.txt.\n";
            std::cout << "File could not be opened.\n";
            std::cout << "\n";

            free_data();

            throw "Unable to open CMakeLists";
        }

        //if(!ext_file->readonly_open())
        //{
        //    std::cout << "\n";
        //    std::cout << "There was an error with loading in read-only files.\n";
        //    std::cout << "Program execution will halt.\n";
        //    std::Cout << "\n";
        //
        //    free();
        //
        //    throw "Unable to open critical read-only file";
        //}
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    text->start();

    // ext_file->read("start.txt");

    early_setup();

    std::cout << linebreak << "\n";
    std::cout << "\n";

    text->package();

    package_setup();

    std::cout << linebreak << "\n";
    std::cout << "\n";

    text->standard();
    
    standard_setup();

    std::cout << "\n";
    std::cout << linebreak << "\n";
    std::cout << "\n";

    verbose_output();

    std::cout << "\n";

    text->source();

    std::cout << "\n";
    std::cout << linebreak << "\n";
    std::cout << "\n";

    // Ask user for any additional directories or included files - TODO

    text->include_dirs();

    std::cout << "\n";
    std::cout << "\n";

    source_and_includes();

    std::cout << linebreak << "\n";
    std::cout << "\n";

    yes_no = 0;

    PACK_LOOP: // Used goto so function doesn't need more declarations

    // Packages / Libraries only
    package_loop();

    text->more_libs();

    input_val(yes_no);

    entry_check();

    // Must be outside a function
    switch(yes_no)
    {
        case 1:
        {
            std::cout << "Understood." << "\n";
            std::cout << "Looping back to library linking." << "\n";
            std::cout << "\n";
            goto PACK_LOOP;

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

    text->promote();

    // Convert into function.

    generate_final();

    std::cout << "\n";
    std::cout << linebreak << "\n";
    std::cout << "\n";

    // move_file();

    // Memory will free automatically from here on.

    std::cout << "The process is finished, you can find your\n";
    std::cout << "CMakeLists.txt file at " << "\n";
    std::cout << ext_file->file_dir << "\n";

    std::cout << db_msg("\n");
    std::cout << db_msg("Files closed.\n");
    std::cout << db_msg("\n");
    std::cout << db_msg("Manager and AltString pointers released.");
    std::cout << db_msg("\n");
    std::cout << db_msg("Memory objects wiped.\n");
    std::cout << db_msg("\n");
    std::cout << db_msg("Reached end of program.\n");
    std::cout << db_msg("\n");

    is_active = false; // Terminate program
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
    input_val(yes_no);
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
    input_val(yes_no);
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
    ext_file->write(text->declare(10));
    ext_file->write("(include)\n");
    //ext_file->write("\n");
    //ext_file->write("# Auto-generated comment:\n");
    //ext_file->write("# Post-compile data\n");
    ext_file->write("\n");

    // Recycle multiple input var here

    if(valid_standard)
    {
        ext_file->write(text->declare(11));
        ext_file->write("(");

        // Ask user about PRIVATE / PUBLIC / INTERFACE preference - TODO

        // Default this to PRIVATE for now
        ext_file->write(text->declare(12));
        ext_file->write(" ");
        ext_file->write(text->declare(14));
        ext_file->write(" ");
        ext_file->write("cxx_std_");
        ext_file->write(actual); // Matches 'standard' int, i.e. 20, 17, etc.
        ext_file->write(")\n");
    }

    yes_no = 0;

    // std::cout << linebreak << "\n";

    text->op_sys();

    std::cout << linebreak << "\n" << "\n";

    sys_flags();

    std::cout << linebreak << "\n" << "\n";

    // win_flags();

    yes_no = 0;
}

void Application::verbose_output()
{
    std::cout << db_msg("\n");
    std::cout << db_msg("Asking user about verbose CMake setting...\n");
    std::cout << db_msg("\n");

    text->verbose();

    yes_no = 0;

    std::cout << "\n";
    std::cout << "Your choice: ";
    input_val(yes_no);

    entry_check();

    switch(yes_no)
    {
        case 1:
        {
            std::cout << "Committing changes to CMakeLists.txt file..." << "\n";
            std::cout << "\n";
            ext_file->write(text->declare(7)); // set
            ext_file->write("(");
            ext_file->write(text->declare(20));
            ext_file->write(" ");
            ext_file->write("true");
            ext_file->write(")");
            ext_file->write("\n");
            ext_file->write("\n");

            if(debug)
            {
                std::cout << "DEBUG DATA:\n";
                std::cout << "Wrote the following to CMakeLists.txt:\n";
                std::cout << text->declare(7);
                std::cout << "(";
                std::cout << text->declare(20);
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

    input_val(yes_no);

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

// These functions will always be checked for input errors.

/// @brief Short function that checks values before it assigns them.
/// @return num
short Application::input_val(short& num)
{
    std::cin >> num;

    entry_check();

    return num;
}

/// @brief Integer function that checks values before it assigns them.
/// @return num
int Application::input_val(int& num)
{
    std::cin >> num;

    entry_check();

    return num;
}

/// @brief Float function that checks values before it assigns them.
/// @return num
float Application::input_val(float& num)
{
    std::cin >> num;

    entry_check();

    return num;
}

/// @brief Function checks if string input is valid. Seperate from numerical input.
/// @return str
std::string Application::input_string(std::string& str)
{
    std::cin >> str;

    entry_check();

    return str;
}

std::string Application::input_longstring(std::string& str)
{
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, str);

    entry_check();

    return str;
}