//
// Created by magupov on 29.08.18.
//

#ifndef ELF_EXPLORER_ELF32_H
#define ELF_EXPLORER_ELF32_H

#include <format/Analyser.h>

class Elf32 : public Analyser {
public:
    Elf32(const std::string &FileName);
    virtual ~Elf32();

    void getHeaderList(std::vector<std::string> &headerList);
};


#endif //ELF_EXPLORER_ELF32_H
