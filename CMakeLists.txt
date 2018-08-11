cmake_minimum_required (VERSION 3.5)
project (elf_expolorer)

set (BINARY_DIR bin)

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )

include_directories(src)

add_subdirectory(src)



