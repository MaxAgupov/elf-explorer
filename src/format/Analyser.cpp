//
// Created by magupov on 29.08.18.
//

#include "Analyser.h"

#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

Analyser::Analyser(const std::string &fileName)
    : file_name(fileName), file_size(0), mem(nullptr)  {
    fd = open(file_name.c_str(), O_RDONLY);
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

Analyser::~Analyser() {
    if (fd) {
        munmap(mem, file_size);
        close(fd);
    }
}
