cmake_minimum_required (VERSION 3.5)
project (elf_expolorer)

set (CMAKE_INCLUDE_CURRENT_DIR on)
set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable (elf_explorer main.cpp)
