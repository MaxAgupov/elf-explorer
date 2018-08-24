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
            FileMenu *menu = new FileMenu(ncurses->screen_width()/2,
                                          ncurses->screen_height(),
                                          ncurses->screen_width()/4, 0);
            bool result = menu->run();
            if (result) {
                analysed_file_name = menu->getChosenFileName();
            }
            delete menu;
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

// control buttons
//    attron(A_REVERSE);
//    mvprintw(main_view.screen_height() - 1, 0,
//            string(main_view.screen_width(), ' ').c_str());
//    attroff(A_REVERSE);

    delete win;
}

