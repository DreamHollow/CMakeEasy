cmake_minimum_required(VERSION 3.24.2)
project(CMakeEasy VERSION 1.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} src/Main.cpp 
src/AltString.cpp 
src/Manager.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Special thanks to LearnQtGuide for his helpful CMake videos.
