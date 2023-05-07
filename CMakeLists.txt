cmake_minimum_required(VERSION 3.22.1)
project(CMakeEasy VERSION 1.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE true)

add_executable(${PROJECT_NAME} src/Main.cpp
src/Manager.cpp
src/AltString.cpp
src/Application.cpp)

include_directories(include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Comment these out if you just want a debug version!
# Custom Statements
if(UNIX)
    message(STATUS "Installing for Linux system...")
    install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
endif()

if(WIN32)
    message(STATUS "Installing for 32 bit Windows...")
    install(TARGETS ${PROJECT_NAME} DESTINATION "C:/Program Files (x86)/CMakeEasy" PERMISSIONS OWNER_EXECUTE)
endif()

if(WIN64)
    message(STATUS "Installing for Windows...")
    install(TARGETS ${PROJECT_NAME} DESTINATION "C:/Program Files/CMakeEasy" PERMISSIONS OWNER_EXECUTE)
endif()

# Auto-generated comment:
# This list made with CMakeEasy.
