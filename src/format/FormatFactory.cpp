//
// Created by magupov on 29.08.18.
//

#include "FormatFactory.h"

#include <format/Analyser.h>
#include <format/Elf32.h>
#include <format/Elf64.h>

#include <elf.h>


Analyser *FormatFactory::createAnalyser(const std::string &fileName) {

    FILE *fp = std::fopen(fileName.c_str(), "r");

    if (!fp) {
        return nullptr;
    }

    char ind[EI_NIDENT];

    // todo: use c++ style
    size_t numread = std::fread((void*)ind, 1, EI_NIDENT, fp);

    if (numread != EI_NIDENT) {
        return nullptr;
    }

    if (ind[EI_MAG0] != ELFMAG0 || ind[EI_MAG1] != ELFMAG1 || ind[EI_MAG2] != ELFMAG2 || ind[EI_MAG3] != ELFMAG3) {
        return nullptr;
    }

    int elf_class = ind[EI_CLASS];

    Analyser *analyser = nullptr;

    switch (elf_class) {
        case ELFCLASS32:
            analyser = new Elf32(fileName);
            break;
        case ELFCLASS64:
            analyser = new Elf64(fileName);
            break;
    }

    std::fclose(fp);
    return analyser;
}
