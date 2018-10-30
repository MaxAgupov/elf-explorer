//
// Created by magupov on 29.08.18.
//

#include "Elf64.h"

#include <elf.h>

#include <format/ElfHeader.h>

Elf64::Elf64(const std::string &FileName)
: Analyser(FileName) {

}

Elf64::~Elf64() {

}

std::string Elf64::getHeaderList(std::vector<std::string> &headerList) {
    if (!fd) {
        return possible_error;
    }

    Elf64_Ehdr *hdr = (Elf64_Ehdr *)mem;

    ElfHeader<Elf64_Ehdr> header(hdr);
    header.toString(headerList);

    return std::string();
}
