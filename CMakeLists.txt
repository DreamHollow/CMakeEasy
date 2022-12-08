cmake_minimum_required(VERSION 3.24.2)
project(CMakeEasy VERSION 1.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} Main.cpp AltString.cpp Manager.cpp)

# Auto-generated comment:
# Made with CMakeEasy.