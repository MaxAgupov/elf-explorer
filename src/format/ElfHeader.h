//
// Created by magupov on 29.08.18.
//

#ifndef ELF_EXPLORER_ELFHEADER_H
#define ELF_EXPLORER_ELFHEADER_H

#include <map>
#include <vector>
#include <sstream>

#include <elf.h>
#include <stdio.h>

template <class HeaderType>
class ElfHeader {
public:
    ElfHeader(HeaderType Header);

    void toString(std::vector<std::string> &stringList);

    std::string getClassString() const;
    std::string getDataString() const;
    std::string getOSAbiString() const;
    std::string getFileTypeString() const;
    std::string getMachineString() const;

private:
    HeaderType header;
};

template<class HeaderType>
ElfHeader<HeaderType>::ElfHeader(HeaderType Header) {
    header = Header;
}

template<class HeaderType>
void ElfHeader<HeaderType>::toString(std::vector<std::string> &stringList) {
    char output_line[256];
    snprintf(output_line, 256, "Class: %s", getClassString().c_str());
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Data: %s", getDataString().c_str());
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Version: %d", (int)header.e_ident[EI_VERSION]);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "OS/ABI: %s", getOSAbiString().c_str());
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "ABI Version: %d", (int)header.e_ident[EI_ABIVERSION]);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Type: %s", getFileTypeString().c_str());
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Machine: %s", getMachineString().c_str());
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Version: %d", header.e_version);
    stringList.push_back(std::string(output_line));

    std::ostringstream entry;
    entry<<"Entry point address: 0x"<<std::hex<<header.e_entry;
    stringList.push_back(entry.str());

    std::ostringstream phoff;
    phoff<<"Start of program headers: "<<header.e_phoff;
    stringList.push_back(phoff.str());

    std::ostringstream shoff;
    shoff<<"Start of section headers: "<<header.e_shoff;
    stringList.push_back(shoff.str());

    snprintf(output_line, 256, "Flags: %u", header.e_flags);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Size of this header: %hu (bytes)", header.e_ehsize);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Size of program headers: %hu (bytes)", header.e_phentsize);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Number of program headers: %hu", header.e_phnum);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Size of section headers: %hu (bytes)", header.e_shentsize);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Number of section headers: %hu", header.e_shnum);
    stringList.push_back(std::string(output_line));
    snprintf(output_line, 256, "Section header string table index: %hu", header.e_shstrndx);
    stringList.push_back(std::string(output_line));
}

template<class HeaderType>
std::string ElfHeader<HeaderType>::getClassString() const {
    switch (header.e_ident[EI_CLASS]) {
        case ELFCLASSNONE:
            return "Invalid";
        case ELFCLASS32:
            return "ELF32";
        case ELFCLASS64:
            return "ELF64";
    }
    return std::string();
}

template<class HeaderType>
std::string ElfHeader<HeaderType>::getDataString() const {
    switch (header.e_ident[EI_DATA]) {
        case ELFDATANONE:
            return "Invalid encoding";
        case ELFDATA2LSB:
            return "2's complement, little endian";
        case ELFDATA2MSB:
            return "2's complement, big endian";
    }
    return std::string();
}

template<class HeaderType>
std::string ElfHeader<HeaderType>::getOSAbiString() const {
    switch (header.e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV:
            return  "UNIX System V ABI";
        case ELFOSABI_HPUX:
            return "HP-UX";
        case ELFOSABI_NETBSD:
            return "NetBSD";
        case ELFOSABI_GNU:
            return "Object uses GNU ELF extensions";
        case ELFOSABI_SOLARIS:
            return "Sun Solaris";
        case ELFOSABI_AIX:
            return "IBM AIX";
        case ELFOSABI_IRIX:
            return "SGI Irix";
        case ELFOSABI_FREEBSD:
            return "FreeBSD";
        case ELFOSABI_TRU64:
            return "Compaq TRU64 UNIX";
        case ELFOSABI_MODESTO:
            return "Novell Modesto";
        case ELFOSABI_OPENBSD:
            return "OpenBSD";
        case ELFOSABI_ARM_AEABI:
            return "ARM EABI";
        case ELFOSABI_ARM:
            return "ARM";
        case ELFOSABI_STANDALONE:
            return "Standalone (embedded) application";
    }

    return std::string();
}

template<class HeaderType>
std::string ElfHeader<HeaderType>::getFileTypeString() const {
    switch (header.e_type) {
        case ET_NONE:
            return "No file type";
        case ET_REL:
            return "Relocatable file";
        case ET_EXEC:
            return "Executable file";
        case ET_DYN:
            return "Shared object file";
        case ET_CORE:
            return "Core file";
        case ET_NUM:
            return "Number of defined types";
        case ET_LOOS:
            return "OS-specific range start";
        case ET_HIOS:
            return "OS-specific range end";
        case ET_LOPROC:
            return "Processor-specific range start";
        case ET_HIPROC:
            return "Processor-specific range end";
    }
    return std::string();
}

template<class HeaderType>
std::string ElfHeader<HeaderType>::getMachineString() const {
    switch(header.e_machine) {
        case EM_NONE:
            return "No machine";
        case EM_M32:
            return "AT&T WE 32100";
        case EM_SPARC:
            return "SUN SPARC";
        case EM_386:
            return "Intel 80386";
        case EM_68K:
            return "Motorola m68k family";
        case EM_88K:
            return "Motorola m88k family";
        case EM_860:
            return "Intel 80860";
        case EM_MIPS:
            return "MIPS R3000 big-endian";
        case EM_S370:
            return "IBM System/370";
        case EM_MIPS_RS3_LE:
            return "MIPS R3000 little-endian";
        case EM_PARISC:
            return "HPPA";
        case EM_VPP500:
            return "Fujitsu VPP500";
        case EM_SPARC32PLUS:
            return "Sun's \"v8plus\"";
        case EM_960:
            return "Intel 80960";
        case EM_PPC:
            return "PowerPC";
        case EM_PPC64:
            return "PowerPC 64-bit";
        case EM_S390:
            return "IBM S390";
        case EM_V800:
            return "NEC V800 series";
        case EM_FR20:
            return "Fujitsu FR20";
        case EM_RH32:
            return "TRW RH-32";
        case EM_RCE:
            return "Motorola RCE";
        case EM_ARM:
            return "ARM";
        case EM_FAKE_ALPHA:
            return "Digital Alpha";
        case EM_SH:
            return "Hitachi SH";
        case EM_SPARCV9:
            return "SPARC v9 64-bit";
        case EM_TRICORE:
            return "Siemens Tricore";
        case EM_ARC:
            return "Argonaut RISC Core";
        case EM_H8_300:
            return "Hitachi H8/300";
        case EM_H8_300H:
            return "Hitachi H8/300H";
        case EM_H8S:
            return "Hitachi H8S";
        case EM_H8_500:
            return "Hitachi H8/500";
        case EM_IA_64:
            return "Intel Merced";
        case EM_MIPS_X:
            return "Stanford MIPS-X";
        case EM_COLDFIRE:
            return "Motorola Coldfire";
        case EM_68HC12:
            return "Motorola M68HC12";
        case EM_MMA:
            return "Fujitsu MMA Multimedia Accelerator";
        case EM_PCP:
            return "Siemens PCP";
        case EM_NCPU:
            return "Sony nCPU embeeded RISC";
        case EM_NDR1:
            return "Denso NDR1 microprocessor";
        case EM_STARCORE:
            return "Motorola Start*Core processor";
        case EM_ME16:
            return "Toyota ME16 processor";
        case EM_ST100:
            return "STMicroelectronic ST100 processor";
        case EM_TINYJ:
            return "Advanced Logic Corp. Tinyj emb.fam";
        case EM_X86_64:
            return "AMD x86-64 architecture";
        case EM_PDSP:
            return "Sony DSP Processor";
        case EM_FX66:
            return "Siemens FX66 microcontroller";
        case EM_ST9PLUS:
            return "STMicroelectronics ST9+ 8/16 mc";
        case EM_ST7:
            return "STmicroelectronics ST7 8 bit mc";
        case EM_68HC16:
            return "Motorola MC68HC16 microcontroller";
        case EM_68HC11:
            return "Motorola MC68HC11 microcontroller";
        case EM_68HC08:
            return "Motorola MC68HC08 microcontroller";
        case EM_68HC05:
            return "Motorola MC68HC05 microcontroller";
        case EM_SVX:
            return "Silicon Graphics SVx";
        case EM_ST19:
            return "STMicroelectronics ST19 8 bit mc";
        case EM_VAX:
            return "Digital VAX";
        case EM_CRIS:
            return "Axis Communications 32-bit embedded processor";
        case EM_JAVELIN:
            return "Infineon Technologies 32-bit embedded processor";
        case EM_FIREPATH:
            return "Element 14 64-bit DSP Processor";
        case EM_ZSP:
            return "LSI Logic 16-bit DSP Processor";
        case EM_MMIX:
            return "Donald Knuth's educational 64-bit processor";
        case EM_HUANY:
            return "Harvard University machine-independent object files";
        case EM_PRISM:
            return "SiTera Prism";
        case EM_AVR:
            return "Atmel AVR 8-bit microcontroller";
        case EM_FR30:
            return "Fujitsu FR30";
        case EM_D10V:
            return "Mitsubishi D10V";
        case EM_D30V:
            return "Mitsubishi D30V";
        case EM_V850:
            return "NEC v850";
        case EM_M32R:
            return "Mitsubishi M32R";
        case EM_MN10300:
            return "Matsushita MN10300";
        case EM_MN10200:
            return "Matsushita MN10200";
        case EM_PJ:
            return "picoJava";
        case EM_OPENRISC:
            return "OpenRISC 32-bit embedded processor";
        case EM_ARC_A5:
            return "ARC Cores Tangent-A5";
        case EM_XTENSA:
            return "Tensilica Xtensa Architecture";
        case EM_ALTERA_NIOS2:
            return "Altera Nios II";
        case EM_AARCH64:
            return "ARM AARCH64";
        case EM_TILEPRO:
            return "Tilera TILEPro";
        case EM_MICROBLAZE:
            return "Xilinx MicroBlaze";
        case EM_TILEGX:
            return "Tilera TILE-Gx";
    }
    return std::string();
}


#endif //ELF_EXPLORER_ELFHEADER_H
