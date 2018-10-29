//
// Created by magupov on 29.08.18.
//

#include "Elf32.h"

#include <elf.h>
#include <fstream>
#include <format/ElfHeader.h>

Elf32::Elf32(const std::string &FileName) : Analyser(FileName) {

}

Elf32::~Elf32() {

}

std::string Elf32::getHeaderList(std::vector<std::string> &headerList) {
    std::ifstream f(file_name, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        return "";
    }
    Elf32_Ehdr hdr;
    f.read((char*) &hdr, sizeof(hdr));
    f.close();

    ElfHeader<Elf32_Ehdr> header(&hdr);
    header.toString(headerList);
}
