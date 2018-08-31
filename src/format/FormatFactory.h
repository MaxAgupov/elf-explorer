//
// Created by magupov on 29.08.18.
//

#ifndef ELF_EXPLORER_ELFVALIDATOR_H
#define ELF_EXPLORER_ELFVALIDATOR_H

#include <string>

class Analyser;

class FormatFactory {
public:
    static Analyser *createAnalyser(const std::string &fileName);
};


#endif //ELF_EXPLORER_ELFVALIDATOR_H
