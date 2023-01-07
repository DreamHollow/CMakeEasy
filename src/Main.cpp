#include "Manager.hpp"
#include <memory>
#include <vector>

int main()
{
    // Heap allocated both classes to prevent overflow of stack.

    std::unique_ptr<Manager> ext_file = std::make_unique<Manager>();
    std::unique_ptr<AltString> text = std::make_unique<AltString>();

    bool debugging = true;
    bool valid_standard = false;
    bool has_package = false;

    char project_name[32];
    char exe_name[32];

    std::string package_name;
    std::string library_segment;
    std::string library_vis; // Library visibility

    std::string declaration;
    std::string requirement;

    std::vector<std::string> packages;

    // Shorts used to avoid unnecessary memory allocation

    short major = 0;
    short minor = 0;
    short release = 0;

    short standard = 0;

    short package_vers = 0;

    // Integer used to avoid problematic char-style input.
    short yes_no = 0;

    text->start();

    std::cout << "Your version: ";
    std::cin >> major;

    if(text->entry_fail(false) != 0)
    {
        return 1;
    }

    // Version numbering (CMake)

    text->minor_vers();

    std::cout << "Your version: ";
    std::cin >> minor;

    if(text->entry_fail(false) != 0)
    {
        return 1;
    }

    text->release_vers();

    std::cout << "Your version: ";
    std::cin >> release;

    if(text->entry_fail(false) != 0)
    {
        return 1;
    }

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
    std::cin.ignore();
    std::cin.getline(project_name,32);

    if(text->entry_fail(true) != 0)
    {
        return 1;
    }

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

    if(text->entry_fail(false) != 0)
    {
        return 1;
    }

    switch(yes_no)
    {
        case 1:
        std::cout << "Please enter the major version number for your program." << "\n";
        std::cout << "Example: [1].0" << "\n";
        std::cout << "Your version: ";
        std::cin >> major;

        if(text->entry_fail(false) != 0)
        {
            return 1;
        }

        std::cout << "Please enter the minor version number for your program." << "\n";
        std::cout << "Example: 1.[0]" << "\n";
        std::cout << "Your version: ";
        std::cin >> minor;

        if(text->entry_fail(false) != 0)
        {
            return 1;
        }

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

    // Finding Packages (may need several invokes)

    text->package();

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

        if(text->entry_fail(false) != 0)
        {
            return 1;
        }

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

            if(text->entry_fail(false))
            {
                return 1;
            }

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

    // Setting operating system procedures

    // text->op_sys();

    text->standard();
    
    std::cout << "Your standard: ";
    std::cin.clear();
    std::cin >> standard;

    std::cout << "\n";

    if(text->entry_fail(false) != 0)
    {
        return 1;
    }

    std::cout << "\n";

    short actual = 0;

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

    std::cout << "\n";

    text->source();

    std::cout << "\n";

    std::string class_name;
    std::string source{ "src/" };

    // Ask user for any additional directories or included files - TODO

    text->include_dirs();

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Please enter the name of your main executable, along with .cpp: ";
    std::cin.ignore();
    std::cin.getline(exe_name, 32);

    if(text->entry_fail(true) != 0)
    {
        return 1;
    }

    ext_file->write(text->declare(8)); // add exe
    ext_file->write("(");
    ext_file->write(text->declare(12));
    ext_file->write(" ");
    ext_file->write(source);
    ext_file->write(exe_name); // should appear as src/(exe_name)

    std::cout << "If your program is using classes, please add your class files." << "\n";
    std::cout << "The program will loop entry until you specify that you are done." << "\n";
    std::cout << "\n";

    bool more_files = false;

    do
    {
        std::cout << "If you have no additional files to include, please enter '!none' instead." << "\n";
        std::cout << "\n";
        std::cout << "Please enter any additional class names. (example: Class.cpp)" << "\n";
        std::cout << "Your next class file: ";

        // Input class name
        std::cin >> class_name;

        if(text->entry_fail(false) != 0)
        {
            return 1;
        }

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

    // Reset var
    yes_no = 0;

    PACK_LOOP:

    // Packages / Libraries only
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

        if(text->entry_fail(false))
        {
            return 1;
        }

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

                    if(text->entry_fail(false) != 0)
                    {
                        return 1;
                    }

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

    text->more_libs();

    std::cin >> yes_no;

    if(text->entry_fail(false) != 0)
    {
        return 1;
    }

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

    if(text->entry_fail(false))
    {
        return 1;
    }

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

    // Force memory to be free for safety reasons

    packages.clear();
    packages.shrink_to_fit();

    ext_file.reset();
    ext_file.release();

    text.reset();
    text.release();

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
    }

    return 0;
};
