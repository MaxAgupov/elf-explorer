//
// Created by Maxim Agupov on 12.08.2018.
//

#ifndef ELF_EXPLORER_FILEMENU_H
#define ELF_EXPLORER_FILEMENU_H

#include "Menu.h"
#include <string>


class FileMenu : public Menu {
public:
    FileMenu(int width, int height, int startx, int starty);

    ~FileMenu();

    bool run();

    void render();

protected:
    void load_directory_content(std::string dir_name);

private:
    std::string current_dir;
};




#endif //ELF_EXPLORER_FILEMENU_H
