#include "Manager.hpp"
#include <memory>
#include <vector>

int main()
{
    // Heap allocated file manager. Just in case.
    std::unique_ptr<Manager> ext_file = std::make_unique<Manager>();
    AltString text_mod;

    bool debugging = true;
    bool valid_standard = false;

    char project_name[32];
    char exe_name[32];
    std::string temp;
    std::string declaration;
    std::vector<std::string> class_names;

    // Shorts used to avoid unnecessary memory allocation

    short major = 0;
    short minor = 0;
    short release = 0;

    short standard = 0;
    // Integer used to avoid problematic char-style input.
    short yes_no = 0;

    short subdir_choice = 0;

    short num_sources = 0;
    short subdir = 0;

    text_mod.start();

    std::cout << "Your version: ";
    std::cin >> major;

    if(text_mod.entry_fail() != 0)
    {
        return 1;
    }

    // Version numbering (CMake)

    text_mod.minor_vers();

    std::cout << "Your version: ";
    std::cin >> minor;

    if(text_mod.entry_fail() != 0)
    {
        return 1;
    }

    text_mod.release_vers();

    std::cout << "Your version: ";
    std::cin >> release;

    if(text_mod.entry_fail() != 0)
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

    ext_file->write("cmake_minimum_required(VERSION ");
    ext_file->write(major);
    ext_file->write(".");
    ext_file->write(minor);
    ext_file->write(".");
    ext_file->write(release);
    ext_file->write(")");
    ext_file->write("\n");

    if(debugging)
    {
        std::cout << "DEBUG:" << "\n";
        std::cout << "Line in file should read as" << "\n";
        std::cout << "'cmake_minimum_required(VERSION x.x.x')" << "\n";
        std::cout << "\n";
    }

    std::cout << "Wrote 'cmake_minimum_required' line automatically." << "\n";
    std::cout << "\n";

    std::cout << "\n";
    std::cout << "Please enter the name of the project that you are trying to create." << "\n";
    std::cout << "\n";
    std::cout << "The input will only handle up to 32 characters, please don't abuse it!" << "\n";
    std::cout << "\n";
    std::cout << "Your project name: ";
    std::cin.ignore();
    std::cin.getline(project_name,32);

    if(text_mod.entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";
    std::cout << "Your project's name has been evaluated as '" << project_name;
    std::cout << "', and will be saved as such." << "\n";
    std::cout << "\n";

    ext_file->write("project(");
    ext_file->write(project_name);

    major = 0;
    minor = 0;

    text_mod.program_vers();
    
    std::cout << "Your choice: ";
    std::cin >> yes_no;

    std::cout << "\n";

    if(text_mod.entry_fail() != 0)
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

        if(text_mod.entry_fail() != 0)
        {
            return 1;
        }

        std::cout << "Please enter the minor version number for your program." << "\n";
        std::cout << "Example: 1.[0]" << "\n";
        std::cout << "Your version: ";
        std::cin >> minor;

        if(text_mod.entry_fail() != 0)
        {
            return 1;
        }

        ext_file->write(" ");
        ext_file->write("VERSION ");
        ext_file->write(major);
        ext_file->write(".");
        ext_file->write(minor);
        ext_file->write(")");

        std::cout << "\n";
        break;

        case 2:
        std::cout << "Understood. No version number will be added to your program build at this time." << "\n";
        std::cout << "\n";

        ext_file->write(")");
        break;
        
        default:
        std::cout << "Sorry, that is not a valid list choice." << "\n";
        std::cout << "Defaulting to choice 2, no program version will be added." << "\n";
        std::cout << "\n";
        break;
    }

    ext_file->write("\n"); // Formats next line no matter what

    yes_no = 0; // Reset the variable

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "DEBUG:" << "\n";
        std::cout << "Line in file should read as" << "\n";
        std::cout << "'project(" << project_name;

        if(major != 0 || minor != 0)
        {
            std::cout << " ";
            std::cout << "VERSION " << major << "." << minor << ")";
        }
        else
        {
            std::cout << ")'";
        }
        std::cout << "\n";
    }

    // Setting modern C++ standards

    text_mod.standard();
    
    std::cout << "Your standard: ";
    std::cin.clear();
    std::cin >> standard;

    std::cout << "\n";

    if(text_mod.entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "\n";

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

            std::cout << "Configuring file for C++20 standards..." << "\n";
            declaration = "CMAKE_CXX_STANDARD 20";
            break;
        }
        case 2:
        {
            valid_standard = true;

            std::cout << "Configuring file for C++17 standards..." << "\n";
            declaration = "CMAKE_CXX_STANDARD 17";
            break;
        }
        case 3:
        {
            valid_standard = true;

            std::cout << "Configuring file for C++14 standards..." << "\n";
            declaration = "CMAKE_CXX_STANDARD 14";
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
        ext_file->write("set(");
        ext_file->write(declaration);
        ext_file->write(")");
        ext_file->write("\n");
    }

    if(debugging)
    {
        if(valid_standard)
        {
            std::cout << "DEBUG:" << "\n";
            std::cout << "Line in file should read as" << "\n";
            std::cout << "'set(" << declaration << ")'" << "\n";
            std::cout << "\n";
        }
        else
        {
            std::cout << "DEBUG:" << "\n";
            std::cout << "Declaration was either invalid or not assigned." << "\n";
        }
    }

    std::cout << "\n";

    text_mod.source();

    std::cout << "\n";

    bool more_files = false;
    short how_many = 0;
    const std::string format = ".cpp";
    std::string class_name;

    std::cout << "Please enter the name of your main executable, along with .cpp: ";
    std::cin.ignore();
    std::cin.getline(exe_name, 32);

    // Check array via string
    temp = exe_name;

    temp.clear();

    ext_file->write("add_executable(${PROJECT_NAME}");
    ext_file->write(" ");
    ext_file->write(exe_name);

    if(text_mod.entry_fail() != 0)
    {
        return 1;
    }

    std::cout << "If your program is using classes, please add your class files." << "\n";
    std::cout << "The program will loop entry until you specify that you are done." << "\n";
    std::cout << "\n";

    more_files = true; // Force first loop

    while(more_files == true)
    {
        std::cout << "If you have no additional files to include, please enter '!none' instead." << "\n";
        std::cout << "\n";
        std::cout << "Please enter any additional class names. (example: Class.cpp)" << "\n";
        std::cout << "Your next class file: ";

        // Input class name
        std::cin >> class_name;

        if(text_mod.entry_fail() != 0)
        {
            return 1;
        }

        if(class_name == "!none")
        {
            std::cout << "\n";
            std::cout << "No additional class names will be added." << "\n";
            std::cout << "\n";

            class_name.clear();

            more_files = false;
        }

        // If the C Plus Plus identifier is not found
        if(!class_name.find(format) != std::string::npos)
        {
            if(!class_name.empty())
            {
                std::cout << "\n";
                std::cout << "Your class file is missing a suffix of .cpp" << "\n";
                std::cout << "Appending suffix..." << "\n";

                class_name.append(".cpp");
                std::cout << "Proper file syntax created: " << class_name << "\n";
                std::cout << "\n";
            }
        }
        
        class_names.push_back(class_name);

        ext_file->write(" ");
        ext_file->write(class_name);
        how_many += 1;

        class_name.erase();
    }    

    ext_file->write(")"); // Close executable entry
    ext_file->write("\n");

    // Set the libraries and dependencies - TODO

    if(debugging)
    {
        std::cout << "\n";
        std::cout << "DEBUG: File closed." << "\n";
        std::cout << "\n";
        std::cout << "DEBUG: Memory objects wiped." << "\n";
        std::cout << "\n";
        std::cout << "DEBUG:" << "\n";
        std::cout << "Reached end of program." << "\n";
    }

    class_names.clear();
    class_names.shrink_to_fit();

    return 0;
};
