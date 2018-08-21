//
// Created by Maxim Agupov on 12.08.2018.
//

#ifndef ELF_EXPLORER_FILEMENU_H
#define ELF_EXPLORER_FILEMENU_H

#include "ListMenu.h"
#include <string>
#include <vector>

class DirEntry : public ItemContent {

public:
    std::string name;
    unsigned char type;
};


class FileMenu : public ListMenu {
public:
    FileMenu(int width, int height, int startx, int starty);

    ~FileMenu();

    bool run();
    std::string getChosenFileName() const;

protected:


    void load_directory_content(std::string dir_name);
protected:
    void preRenderItem(ListMenuItem *item);
    void postRenderItem(ListMenuItem *item);
    void clearContent();
    void sortItems();

    bool handleEnter();
private:
    std::string current_dir;

    std::vector<DirEntry*> content;
};




#endif //ELF_EXPLORER_FILEMENU_H
