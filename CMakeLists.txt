cmake_minimum_required(VERSION 3.10)

project(str_problem CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable
add_executable(code main.cpp)

# Include the current directory for header files
target_include_directories(code PRIVATE .)