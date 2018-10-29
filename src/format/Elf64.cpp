//
// Created by magupov on 29.08.18.
//

#include "Elf64.h"

#include <elf.h>
#include <fstream>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include <format/ElfHeader.h>

Elf64::Elf64(const std::string &FileName)
: Analyser(FileName), file_size(0), mem(nullptr) {
    fd = open(FileName.c_str(), O_RDONLY);
    if (fd < 0) {
        possible_error = std::strerror(errno);
        fd = 0;
        return;
    }
    struct stat st;
    if (fstat(fd, &st) < 0) {
        possible_error = std::strerror(errno);
        close(fd);
        fd = 0;
        return;
    }
    file_size = (size_t) st.st_size;
    mem = mmap(0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED) {
        possible_error = std::strerror(errno);
        close(fd);
        fd = 0;
        mem = NULL;
        return;
    }
}

Elf64::~Elf64() {
    if (fd) {
        munmap(mem, file_size);
        close(fd);
    }
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
