//
// Created by magupov on 29.08.18.
//

#include "Elf32.h"

#include <elf.h>

#include <format/ElfHeader.h>

Elf32::Elf32(const std::string &FileName) : Analyser(FileName) {

}

Elf32::~Elf32() {

}

std::string Elf32::getHeaderList(std::vector<std::string> &headerList) {
    if (!fd) {
        return possible_error;
    }

    Elf32_Ehdr *hdr = (Elf32_Ehdr *)mem;

    ElfHeader<Elf32_Ehdr> header(hdr);
    header.toString(headerList);

    return std::string();
}
