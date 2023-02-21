#include "Application.hpp"

Application::Application()
{
    this->init_vars();
    this->init_components();
}

Application::~Application()
{

}

void Application::init_vars()
{
    // Do not alter debugging state except in Globals.h

    is_active = true;
    text = nullptr;
    ext_file = nullptr;

    valid_standard = false;
    has_package = false;
}

void Application::init_components()
{
    text = std::make_unique<AltString>();
    ext_file = std::make_unique<Manager>();
}

/// @brief Absolute call to free memory, just in case.
void Application::free()
{
    packages.clear();
    packages.shrink_to_fit();

    if(text == nullptr)
    {
        text.release();
    }
    else
    {
        text.reset();
    }

    if(ext_file == nullptr)
    {
        ext_file.release();
    }
    else
    {
        ext_file.reset();
    }

    if(debugging)
    {
        std::cout << "DEBUG: " << "'text' and 'ext_file' pointers released safely." << "\n";
    }
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

            // Free held memory
            this->free();

            throw "Invalid data input!";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what();
    }
}

void Application::pre_setup()
{
    const char disp_warn[] = "Do you permit CMakeEasy to display and use your Documents folder?";

    yes_no = 0;

    if(debugging)
    {
        std::cout << db_string << "yes_no forced to 0." << "\n";
        std::cout << db_string << "Searching for 'Documents' dir..." << "\n";
        std::cout << "\n";
    }

    if(OS_WINDOWS)
    {
        std::cout << disp_warn;
        std::cout << "1. Yes, I permit the program to use 'My Documents' folder." << "\n";
        std::cout << "2. No, I don't permit this." << "\n";
        std::cout << "Your choice: ";
        std::cin >> yes_no;

        switch(yes_no)
        {
            case 1:
            {
                std::cout << "Understood. CMakeEasy will be permitted to use \n";
                // Get user documents dir
                
                std::cout << "as the directory to save the CMakeLists.txt file.\n";
                break;
            }
            case 2:
            {
                std::cout << "Understood. CMakeEasy will not use 'My Documents' as\n";
                std::cout << "the save location for CMakeLists.txt" << "\n";
                std::cout << "Defaulting to\n";
                system("echo %cd%");
                std::cout << "\n";
                break;
            }
            default:
            {
                std::cout << "This input was unrecognized. Defaulting to 2, 'no'.\n";
                break;
            }
        }

        //system("echo %cd%");
    }

    if(!OS_WINDOWS) // Linux
    {
        std::cout << disp_warn;
        std::cout << "1. Yes, I permit the program to use 'My Documents' folder." << "\n";
        std::cout << "2. No, I don't permit this." << "\n";
        std::cout << "Your choice: ";
        std::cin >> yes_no;

            switch(yes_no)
            {
            case 1:
            {
                std::cout << "Understood. CMakeEasy will be permitted to use \n";
                // Get user documents dir
                
                std::cout << "as the directory to save the CMakeLists.txt file.\n";
            }
            case 2:
            {
                std::cout << "Understood. CMakeEasy will not use your 'Documents' folder as\n";
                std::cout << "the save location for CMakeLists.txt" << "\n";
                std::cout << "\n";
                std::cout << "Defaulting to your root or home directory." << "\n";
                std::cout << "\n";
                break;
            }
            default:
            {
                std::cout << "This input was unrecognized. Defaulting to 2, 'no'.\n";
                break;
            }
        }

        //system("pwd");
    }

    yes_no = 0; // Reset to null

    if(debugging)
    {
        std::cout << db_string << "yes_no is reset to 0." << "\n";
    }
}

void Application::early_setup()
{
    std::cout << "Your version: ";
    std::cin >> major;

    entry_check();

    // Version numbering (CMake)

    text->minor_vers();

    std::cout << "Your version: ";
    std::cin >> minor;

    entry_check();

    text->release_vers();

    std::cout << "Your version: ";
    std::cin >> release;

    entry_check();

    std::cout << "Configuring line inputs..." << "\n";
    std::cout << "You have designated your version of CMake as ";
    std::cout << major << "." << minor << "." << release << "\n";
    std::cout << "\n";
    std::cout << "Please keep in mind that if this is wrong," << "\n";
    std::cout << "you will have to start this process over." << "\n";

    // Start writing actual CMakeFile
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

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "DEBUG:" << "\n";
        std::cout << "Line in file should read as" << "\n";
        std::cout << "'cmake_minimum_required(VERSION x.x.x')" << "\n";
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
    std::cin >> project_name;

    entry_check();

    std::cout << "\n";
    std::cout << "Your project's name has been evaluated as '" << project_name;
    std::cout << "', and will be saved as such." << "\n";
    std::cout << "\n";

    ext_file->write(text->declare(1));
    ext_file->write("(");
    ext_file->write(project_name);

    major = 0;
    minor = 0;

    text->program_vers();
    
    std::cout << "Your choice: ";
    std::cin >> yes_no;

    std::cout << "\n";

    entry_check();

    switch(yes_no)
    {
        case 1:
        std::cout << "Please enter the major version number for your program." << "\n";
        std::cout << "Example: [1].0" << "\n";
        std::cout << "Your version: ";
        std::cin >> major;

        entry_check();

        std::cout << "Please enter the minor version number for your program." << "\n";
        std::cout << "Example: 1.[0]" << "\n";
        std::cout << "Your version: ";
        std::cin >> minor;

        entry_check();

        ext_file->write(" ");
        ext_file->write(text->declare(2));
        ext_file->write(" ");
        ext_file->write(major);
        ext_file->write(".");
        ext_file->write(minor);

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

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "Line should read as: " << "\n";
        std::cout << text->declare(1) << "(" << project_name << " ";

        if(major && minor != 0)
        {
            std::cout << text->declare(2) << " " << major << "." << minor;
        }

        std::cout << " ";
        std::cout << text->declare(3);
        std::cout << ")";
        std::cout << "\n";
    }
}

void Application::package_setup()
{
    do
    {
        std::cout << "Please enter any extra packages you would like to add." << "\n";
        std::cout << "\n";
        std::cout << "Please note that you can enter packages one after another, then you will\n";
        std::cout << "be asked to add the relevant components afterward." << "\n";
        std::cout << "\n";
        std::cout << "If you don't want to add any more packages, just type '!none' instead." << "\n";
        std::cout << "Your package: ";
        std::cin >> package_name;

        entry_check();

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
            std::cin >> package_vers;

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
            std::cin >> yes_no;

            entry_check();

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

            if(debugging)
            {
                std::cout << "\n";
                std::cout << "DEBUG:\n";
                std::cout << package_name << " was added to 'packages' vector." << "\n";
                std::cout << "\n";
            }

            ext_file->write(text->declare(19)); // find_package
            ext_file->write("(");
            ext_file->write(package_name);

            // If package version is relevant
            if(package_vers != 0)
            {
                ext_file->write(" ");
                ext_file->write(package_vers);
                ext_file->write(" ");
            }

            if(req_package)
            {
                ext_file->write(text->declare(17));
            }

            ext_file->write(")");

            has_package = true;
        }

        ext_file->write("\n");

    }while(package_name != "!none");

    package_name.clear();
}

void Application::standard_setup()
{
    std::cout << "Your standard: ";
    std::cin.clear();
    std::cin >> standard;

    std::cout << "\n";

    entry_check();

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
            if(debugging)
            {
                std::cout << "\n";
                std::cout << "DEBUG:";
                std::cout << "'standard' was assigned to the number 4." << "\n";
                std::cout << "\n";
            }
            break;
        }
        case 1:
        {
            valid_standard = true;
            actual = 20;

            std::cout << "Configuring file for C++20 standards..." << "\n";
            declaration = text->declare(6);
            declaration.append(" " + std::to_string(actual));
            break;
        }
        case 2:
        {
            valid_standard = true;
            actual = 17;

            std::cout << "Configuring file for C++17 standards..." << "\n";
            declaration = text->declare(6);
            declaration.append(" " + std::to_string(actual));
            break;
        }
        case 3:
        {
            valid_standard = true;
            actual = 14;

            std::cout << "Configuring file for C++14 standards..." << "\n";
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

    if(debugging)
    {
        if(valid_standard)
        {
            std::cout << "\n";
            std::cout << "DEBUG:" << "\n";
            std::cout << "Line in file should read as" << "\n";
            std::cout << text->declare(7) << "(" << declaration << ")'" << "\n";
            std::cout << "'" << requirement << "'" << "\n";
            std::cout << "\n";
        }
        else
        {
            std::cout << "\n";
            std::cout << "DEBUG:" << "\n";
            std::cout << "Declaration was either invalid or not assigned." << "\n";
        }
    }
}

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

        std::cin >> yes_no;

        entry_check();

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
                std::cout << "Your library: ";
                std::cin >> library_shorthand;

                library_shorthand.append("-"); // Append a dash

                // Shorthand NOT written yet

                // Ask about PUBLIC, PRIVATE, INTERFACE - TODO

                do
                {
                    std::cout << "Please link library components." << "\n";
                    std::cout << "Library components can be linked with a dash, but one will be provided for you." << "\n";
                    std::cout << "\n";
                    std::cout << "If you have no library components to link, please enter '!none' and your" << "\n";
                    std::cout << "unused entry will be excluded from the CMakeLists.txt file.";
                    std::cout << "\n";
                    std::cout << "Please enter any additional library components. (example: sfml-graphics)" << "\n";
                    std::cout << "\n";
                    std::cout << "Your next library target: ";

                    std::cin >> library_segment;

                    entry_check();

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

void Application::source_and_includes()
{
    std::cout << "Please enter the name of your main executable, along with .cpp: ";
    std::cin >> exe_name;

    entry_check();

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
        std::cin >> class_name;

        entry_check();

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
        }

        if(more_files)
        {
            ext_file->write("\n"); // Seperator
        }
        ext_file->write(source);
        ext_file->write(class_name);

        class_name.erase();
    }while(more_files);

    ext_file->write(")\n");
}

void Application::run()
{
    // Don't use this right now,
    // need a better way to get My Documents from user's home machine

    // text->select_dir();

    // Select directory

    text->start();

    early_setup();

    text->package();

    package_setup();

    // Setting operating system procedures

    // text->op_sys();

    text->standard();
    
    standard_setup();

    std::cout << "\n";

    text->source();

    std::cout << "\n";

    // Ask user for any additional directories or included files - TODO

    text->include_dirs();

    std::cout << "\n";
    std::cout << "\n";

    source_and_includes();

    yes_no = 0;

    PACK_LOOP: // Used goto so function doesn't need more declarations

    // Packages / Libraries only
    package_loop();

    text->more_libs();

    std::cin >> yes_no;

    entry_check();

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

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "DEBUG: " << "Writing additional standards info..." << "\n";
        std::cout << "\n";
    }

    // Set standard include directory

    ext_file->write("\n");
    ext_file->write(text->declare(10));
    ext_file->write("(include)\n");

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

    text->promote();

    std::cin >> yes_no;

    entry_check();

    switch(yes_no)
    {
        case 1:
        std::cout << "Automatically generating comment..." << "\n";

        ext_file->write("\n");
        ext_file->write("# Auto-generated comment:\n");
        ext_file->write("# This list made with CMakeEasy.\n");

        std::cout << "\n";
        std::cout << "Comment generated." << "\n";

        break;
        case 2:
        std::cout << "Okay. No comment will be generated." << "\n";
        break;
        default:
        std::cout << "Sorry, that is not a valid list choice." << "\n";
        std::cout << "Defaulting to 'no'." << "\n";
        break;
    }

    move_file();

    // Memory will free automatically from here on.

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "DEBUG: File closed." << "\n";
        std::cout << "\n";
        std::cout << "DEBUG: Manager and AltString pointers released." << "\n";
        std::cout << "\n";
        std::cout << "DEBUG: Memory objects wiped." << "\n";
        std::cout << "\n";
        std::cout << "DEBUG:" << "\n";
        std::cout << "Reached end of program." << "\n";
        std::cout << "\n";
    }

    is_active = false;
}

void Application::move_file()
{
    yes_no = 0;

    if(debugging)
    {
        std::cout << "DEBUG: Starting file moving operation..." << "\n";
        std::cout << "\n";
    }

    std::cout << "Would you like to move your CMakeLists.txt file into it's own directory?" << "\n";
    std::cout << "A folder will be created and named 'CMake Auto Lists'. It can only contain\n";
    std::cout << "one CMakeLists.txt file at a time." << "\n";
    std::cout << "\n";

    std::cout << "1. Yes, I would like to move the list to folder 'CMake Auto Lists'." << "\n";
    std::cout << "2. No, I want to keep the file I created where it is." << "\n";
    std::cout << "\n";
    std::cout << "Your choice: ";
    std::cin >> yes_no;

    entry_check();

    switch(yes_no)
    {
        case 1:
        {
            std::cout << "Understood. Now moving 'CMakeLists.txt' to 'CMake Auto Lists'." << "\n";
            if(OS_WINDOWS)
            {
                if(debugging)
                {
                    std::cout << "DEBUG: Windows file protocols started." << "\n";
                }

                system("mkdir CMake_Auto_Lists");
                system("move -y 'CMakeLists.txt' 'CMake_Auto_Lists'");

                if(debugging)
                {
                    std::cout << "DEBUG: Windows protocols finished." << "\n";
                }
            }

            if(!OS_WINDOWS) // Linux
            {
                if(debugging)
                {
                    std::cout << "DEBUG: Linux file protocols started." << "\n";
                }

                system("mkdir 'CMake Auto Lists'");
                system("mv 'CMakeLists.txt' 'CMake Auto Lists'");

                if(debugging)
                {
                    std::cout << "DEBUG: Linux protocols finished." << "\n";
                }
            }

            if(debugging)
            {
                std::cout << "DEBUG: File moving operation concluded." << "\n";
            }

            break;
        }
        case 2:
        {
            // Continue normal operation
            std::cout << "Understood. The CMakeLists.txt file should be in the same directory as CMakeEasy." << "\n";

            if(debugging)
            {
                std::cout << "DEBUG: File moving operation not performed." << "\n";
            }

            break;
        }
        default:
        {
            std::cout << "Sorry, that is not a valid choice. Defaulting to choice 2: No." << "\n";

            if(debugging)
            {
                std::cout << "DEBUG: File moving operation cancelled." << "\n";
            }

            break;
        }
    }
}