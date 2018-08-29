//
// Created by magupov on 21.08.18.
//

#include <string>

#include "DisplayManager.h"
#include <view/NCurses.h>
#include <view/Window.h>
#include <view/FileMenu.h>

DisplayManager::DisplayManager()
    : is_shown(false) {
    ncurses = new NCurses();
}

DisplayManager::~DisplayManager() {
    delete ncurses;
}

void DisplayManager::show() {
    is_shown = true;

    std::string analysed_file_name;

    Window *win = new Window(ncurses->screen_width(), ncurses->screen_height(), 0, 0);

    do {
        win->render();

        if (analysed_file_name.empty()) {
            chooseFile(analysed_file_name);
            win->openFile(analysed_file_name);
        } else {
            switch (win->getCh()) {
                case KEY_F(10):
                    is_shown = false;
                    break;
                default:
                    break;
            }
        }
    } while (is_shown);
    delete win;
}

void DisplayManager::chooseFile(std::string &chosen_file) {
    FileMenu *menu = new FileMenu(ncurses->screen_width()/2,
                                  ncurses->screen_height(),
                                  ncurses->screen_width()/4, 0);
    bool result = menu->run();
    if (result) {
        chosen_file = menu->getChosenFileName();
    }
    delete menu;
}

