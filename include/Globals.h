#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED 1

#ifdef _WIN32
#define OS_WIN 1
#include <windows.h>
#endif

#ifdef __linux__ // Linux
#define OS_WIN 0
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
static struct passwd *pw = getpwuid(getuid());
static const char *homedir = pw->pw_dir;
#endif

#ifdef _WIN64
#define OS_WIN 1
#include <windows.h>
#endif

#include <string>

static const bool debug = false;
static const char db_string[]{"DEBUG: "};
static short yes_no = 0;
// static char exit_cmd[]{ "!exit" };

/// @brief Static function that checks if debugging is on,
/// then adds debug data where appropriate.
static std::string db_msg(std::string msg)
{
    std::string nextline = "\n";
    const std::string nullstring = "";

    if(debug)
    {
        if(msg == nextline)
        {
            return nextline;
        }

        return (db_string + msg);
    }

    if(msg == nextline) // Not debug
    {
        return nullstring;
    }

    return nullstring;
}

#endif