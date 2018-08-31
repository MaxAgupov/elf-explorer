//
// Created by magupov on 29.08.18.
//

#ifndef ELF_EXPLORER_ELF64_H
#define ELF_EXPLORER_ELF64_H

#include <format/Analyser.h>

#include <vector>
#include <string>

class Elf64 : public Analyser{
public:
    Elf64(const std::string &FileName);

    void getHeaderList(std::vector<std::string> &headerList);
    virtual ~Elf64();
};


#endif //ELF_EXPLORER_ELF64_H
