#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>

#include <ncurses.h>

#ifdef LINUX
#include <elf.h>
#endif

using namespace std;

int main(int argc, char** argv) {
//	if (argc != 2) {
//		cerr<<"Using: ekf_explorer <file_name>"<<endl;
//		return 1;
//	}
//
//	FILE *fp = std::fopen(argv[1], "r");
//
//	if (!fp) {
//		cerr<<"Cannot open file "<<argv[1]<<": "<<std::strerror(errno)<<endl;
//		return 1;
//	}


	initscr();
	printw("Hello world");

	refresh();
	getch();
	endwin();

#ifdef LINUX
	char ind[EI_NIDENT];
	
	size_t numread = std::fread((void*)ind, 1, EI_NIDENT, fp);
	
	if (numread != EI_NIDENT) {
		cerr<<"File is too short"<<endl;
		return 1;
	}

	if (ind[EI_MAG0] != ELFMAG0 || ind[EI_MAG1] != ELFMAG1 || ind[EI_MAG2] != ELFMAG2 || ind[EI_MAG3] != ELFMAG3) {
		cerr<<"Wrong file format. Must be ELF"<<endl;
		return 1;
	}
	
	int elf_class = ind[EI_CLASS];
	int elf_endian = ind[EI_DATA];

	cout<<"class="<<(elf_class==ELFCLASS32?"32bit":(elf_class==ELFCLASS64?"64bit":"none"))<<endl;
#endif

//	std::fclose(fp);

	return 0;
}

