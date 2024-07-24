cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Mamba)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
