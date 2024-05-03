cmake_minimum_required(VERSION 3.22.1)
project(cmakeeasy VERSION 1.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

add_executable(${PROJECT_NAME} src/Main.cpp
src/AltString.cpp
src/Application.cpp
src/Manager.cpp)

include_directories(include)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Manually added this, feature is coming soon

# This should work for any OS
add_custom_target(copy_resources ALL
COMMAND ${CMAKE_COMMAND} -E copy_directory
${PROJECT_SOURCE_DIR}/src/text
${PROJECT_BINARY_DIR}/text
COMMENT "Copying text resources into 'text' folder...")

#end manual input

# If `make install` is run then it actually installs
if(WIN32)
   message(STATUS "Preparing data for Windows system...")
   install(TARGETS ${PROJECT_NAME} DESTINATION "C:/Program Files/cmakeeasy" PERMISSIONS GROUP_EXECUTE)
   install(DIRECTORY src/text/ DESTINATION "C:/Program Files/cmakeeasy/text")
endif()

if(UNIX)
   message(STATUS "Preparing data for Linux system...")
   install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
   install(DIRECTORY src/text/ DESTINATION etc/cmakeeasy)
endif()

# Auto-generated comment:
# This list made with CMakeEasy.
