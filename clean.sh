#!/bin/sh

# Only works for debug version of CMakeEasy
# Do not modify this file! It may cause issues.

BUILD_DIR='build'
DEBUG_DIR='Debug'
RELEASE_DIR='Release'

if [ -d $BUILD_DIR ]
then
    rm -r $BUILD_DIR

    if [ -d $BUILD_DIR ] # interrupt because clean failed
    then
        echo "ERROR: $BUILD_DIR would not allow clean!"
        echo "Please check user permissions."
        return 1
    fi
else
    echo "No older format 'build' directory found, moving on..."
fi

if [ -d $DEBUG_DIR ]
then
    rm -r $DEBUG_DIR

    if [ -d $DEBUG_DIR ]
    then
        echo "ERROR: $DEBUG_DIR would not allow clean!"
        echo "Please check user permissions."
        return 1
    fi
else
    echo "No $DEBUG_DIR directory present, moving on..."
fi

if [ -d $RELEASE_DIR ]
then
    rm -r $RELEASE_DIR

    if [ -d $RELEASE_DIR ]
    then
        echo "ERROR: $RELEASE_DIR would not allow clean!"
        echo "Please check user permissions."
        return 1
    fi
else
    echo "No $RELEASE_DIR directory present, moving on..."
fi

echo "Cleaning finished."

return 0