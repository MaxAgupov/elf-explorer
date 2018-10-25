//
// Created by magupov on 21.08.18.
//

#include <string>

#include "DisplayManager.h"
#include <view/MainWindow.h>
#include <view/FileMenu.h>

DisplayManager::DisplayManager() {
    initNcurses();
}

DisplayManager::~DisplayManager() {
    endNcurses();
}

void DisplayManager::show() {
    bool is_shown = true;
    bool choose_file = false;

    std::string analysed_file_name;

    MainWindow *win = new MainWindow(screen_width(), screen_height(), 0, 0);

    do {
        win->render();
        if (choose_file) {
            choose_file = false;
            chooseFile(analysed_file_name);
            win->openFile(analysed_file_name);
        } else {
            int ch = win->getCh();
            win->processKeyboard(ch);
            switch (ch) {
                case KEY_F(2):
                    choose_file = true;
                    break;
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
    FileMenu *menu = new FileMenu(screen_width()/2,
                                  screen_height(),
                                  screen_width()/4,
                                  0);
    bool result = menu->run();
    if (result) {
        chosen_file = menu->getChosenFileName();
    }
    delete menu;
}

void DisplayManager::initNcurses(){
    initscr();
    noecho();
    cbreak();
    raw();
    curs_set(0);
    keypad(stdscr, true);

    refresh();
}

void DisplayManager::endNcurses() {
    endwin();
}

int DisplayManager::screen_width() const {
    return COLS;
}

int DisplayManager::screen_height() const {
    return LINES;
}
