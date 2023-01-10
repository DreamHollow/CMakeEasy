cmake_minimum_required(VERSION 3.22.1)
project(CMakeEasy VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Manually added
configure_file(CMakeEasyConfig.h.in CMakeEasyConfig.h)

add_executable(${PROJECT_NAME} src/Main.cpp
src/AltString.cpp
src/Manager.cpp
src/Application.cpp)

include_directories(include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
# Manually added
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# Auto-generated comment:
# This list made with CMakeEasy.
