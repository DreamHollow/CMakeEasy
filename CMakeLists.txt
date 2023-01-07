cmake_minimum_required(VERSION 3.22.1)
project(CMakeEasy VERSION 1.0 LANGUAGES CXX)

configure_file(CMakeEasyConfig.h.in CMakeEasyConfig.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/Main.cpp
src/AltString.cpp
src/Manager.cpp)

include_directories(include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)