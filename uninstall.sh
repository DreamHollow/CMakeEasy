#!/bin/sh
# Only works on Linux
# Use sudo/wheel permissions just like install.sh

old_database="/opt/cmakeeasy"
text_database="/usr/local/etc/cmakeeasy"
prog="/usr/local/bin/cmakeeasy"

# There are easier ways to do this, but this works.
echo "This operation will uninstall CMakeEasy from your system."
read -p "Continue? (Y/N) " confirm
case $confirm in
    Y)
    echo "Confirmed. Uninstalling CMakeEasy..."

    if [ -d "$old_database" ]
    then
        echo "Found old opt directory at '$old_database'"
        echo "Uninstalling..."
        rm -r $old_database
        echo "CMakeEasy opt files uninstalled."
    else
        echo "No old opt directory present."
        echo
    fi

    if [ -d "$text_database" ]
    then
        echo "Found etc directory at '$text_database'"
        echo "Uninstalling..."
        rm -r $text_database
        rm -r $prog
        echo "CMakeEasy etc files uninstalled."
    else
        echo "No etc directory present, no files to uninstall."
        echo
    fi

    if [ -f "$prog" ]
    then
        echo "Found binary at '$main_prog'"
        echo "Uninstalling..."
        rm -r $prog
        echo "CMakeEasy binary uninstalled."
    else
        echo "No binary found at expected location."
        echo
    fi

    echo "Uninstall complete."

    ;;
    y)
    echo "Confirmed. Uninstalling CMakeEasy..."

    if [ -d "$old_database" ]
    then
        echo "Found old opt directory at '$old_database'"
        echo "Uninstalling..."
        rm -r $old_database
        echo "CMakeEasy opt files uninstalled."
    else
        echo "No old opt directory present."
        echo
    fi

    if [ -d "$text_database" ]
    then
        echo "Found etc directory at '$text_database'"
        echo "Uninstalling..."
        rm -r $text_database
        echo "CMakeEasy etc files uninstalled."
    else
        echo "No etc directory present, no files to uninstall."
        echo
    fi

    if [ -f "$prog" ]
    then
        echo "Found binary at '$prog'"
        echo "Uninstalling..."
        rm -r $prog
        echo "CMakeEasy binary uninstalled."
    else
        echo "No binary found at expected location."
        echo
    fi

    echo "Uninstall complete."

    ;;
    N)
    echo "Understood, CMakeEasy will not be uninstalled."
    ;;
    n)
    echo "Understood, CMakeEasy will not be uninstalled."
    ;;
    *)
    echo "Unknown response. CMakeEasy will not be uninstalled."
    ;;
esac
