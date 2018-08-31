add_executable(elf_explorer main.cpp App.cpp ../format/FormatFactory.cpp ../format/FormatFactory.h)

target_link_libraries(elf_explorer view)