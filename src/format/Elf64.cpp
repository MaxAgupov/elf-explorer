//
// Created by magupov on 29.08.18.
//

#include "Elf64.h"

#include <elf.h>
#include <fstream>

#include <format/ElfHeader.h>

Elf64::Elf64(const std::string &FileName) : Analyser(FileName) {

}

Elf64::~Elf64() {

}

void Elf64::getHeaderList(std::vector<std::string> &headerList) {

    std::ifstream f(file_name, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        perror("Error");
        return;
    }
    Elf64_Ehdr hdr;
    f.read((char*) &hdr, sizeof(hdr));
    f.close();

    ElfHeader<Elf64_Ehdr> header(hdr);
    header.toString(headerList);
}
