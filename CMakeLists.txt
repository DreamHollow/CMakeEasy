cmake_minimum_required(VERSION 3.22.1)
project(CMakeEasy VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE true)

# Manually added

if((DEFINED CMAKE_BUILD_TYPE) AND (NOT CMAKE_BUILD_TYPE STREQUAL ""))
    message("CMake build type is not declared!")
else()
    message("CMake build type was found.")
endif()

# Manually added
configure_file(CMakeEasyConfig.h.in CMakeEasyConfig.h)

# Manually added
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("CMAKE_CXX_FLAGS_MINSIZEREL: ${CMAKE_CXX_FLAGS_MINSIZEREL}")

add_executable(${PROJECT_NAME} src/Main.cpp
src/AltString.cpp
src/Manager.cpp
src/Application.cpp)

include_directories(include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
# Manually added
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# Comment this out if you are just testing!
#install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#install(FILES "${PROJECT_BINARY_DIR}/CMakeEasyConfig.h" DESTINATION include)

# Auto-generated comment:
# This list made with CMakeEasy.
