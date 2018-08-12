//
// Created by Maxim Agupov on 11.08.2018.
//

#ifndef ELF_EXPLORER_MENU_H
#define ELF_EXPLORER_MENU_H

#include <ncurses.h>
#include <string>


class Menu {
public:
    Menu(int width, int height, int startx, int starty);

    virtual ~Menu();

    virtual bool run() = 0;
    virtual void render();

protected:
    WINDOW *menu;
    int width;
    int height;
    int startx;
    int starty;
};


#endif //ELF_EXPLORER_MENU_H
