#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __unix__ // Linux
#define OS_WINDOWS 0
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
static struct passwd *pw = getpwuid(getuid());
static const char *homedir = pw->pw_dir;
#endif

#ifdef _WIN32
#define OS_WINDOWS 1
#include <windows.h>
#endif

#ifdef _WIN64
#define OS_WINDOWS 1
#include <windows.h>
#endif

#include <string>

static bool debug = true;
static char db_string[]{"DEBUG: "};
static short yes_no = 0;
static char exit[]{ "!exit" };

static std::string db_msg(std::string msg);

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
        return nextline;
    }

    return nullstring;
}

#endif