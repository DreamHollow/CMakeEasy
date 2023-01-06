cmake_minimum_required(VERSION 3.22.1)
project(CMakeEasy VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/Main.cpp
src/AltString.cpp
src/Manager.cpp)

include_directories(include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Auto-generated comment:
# This list made with CMakeEasy.
