//
// Created by Maxim Agupov on 11.08.2018.
//

#include "Menu.h"


Menu::Menu(int width, int height, int startx, int starty)
 : width(width), height(height), startx(startx), starty(starty) {
    menu = newwin(height, width, starty, startx);
    box(menu, 0, 0);
}

Menu::~Menu() {
    delwin(menu);
}

void Menu::render() {
    wrefresh(menu);
}





