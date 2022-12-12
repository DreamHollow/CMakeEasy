cmake_minimum_required(VERSION 3.25.0)
project(CMakeEasy VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANARD_REQUIRED ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
add_executable(${PROJECT_NAME} src/Main.cpp
       src/AltString.cpp
       src/Manager.cpp)

include_directories(include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Special thanks to LearnQtGuide for his helpful CMake videos.

# This CMakeEasy file has been modified slightly,
# CMakeEasy is NOT entirely feature complete.

# Auto-generated comment:
# This list MOSTLY made with CMakeEasy.
