cmake_minimum_required(VERSION 3.22.1)
project(cmakeeasy VERSION 1.3.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE true)

add_executable(${PROJECT_NAME} src/Main.cpp
src/Manager.cpp
src/AltString.cpp
src/Application.cpp)

include_directories(include)

# Auto-generated comment:
# Post-compile data

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(WIN32)
   message(STATUS "Installing for Windows...")
   install(TARGETS ${PROJECT_NAME} DESTINATION "C:/Program Files/CMakeEasy" PERMISSIONS OWNER_EXECUTE)
endif()

if(UNIX)
   message(STATUS "Installing for Linux...")
   install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
endif()

# Auto-generated comment:
# This list made with CMakeEasy.
