# Minimum Cmake verison required
cmake_minimum_required(VERSION 3.0.0)

# Project name 
project(gpio-http-api-example-cpp VERSION 0.1.0)

# Global Install Directories
include(GNUInstallDirs)

# ----------------------------------
#    Section for compiling 1 binary 
# ----------------------------------
# Compile for one binary

# List all the files for compiling one binary
set(BIN_SRC_FILES
    src/main.cpp
    src/gpioapi.cpp)

add_executable(gpio-http-api-example-cpp ${BIN_SRC_FILES})

# Define Compiler Flags to your library
target_compile_options(gpio-http-api-example-cpp  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic>)

# Define the Include directories 
# <BUILD_INTERFACE> for those directories that are needed for compilation.
target_include_directories(gpio-http-api-example-cpp  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

# If you have any more external libraries to link then link here 
target_link_libraries(gpio-http-api-example-cpp  PUBLIC -lm -lcurl )
# ----------------------------------
#    End Section for binary
# ----------------------------------
# If you have multiple binaries in a folder 
# the add more of these sections and change binary_name

