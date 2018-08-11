//
// Created by max on 10.08.18.
//

#include <ncurses.h>

#include "NCurses.h"


NCurses::NCurses() {

}

void NCurses::init() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
}

void NCurses::end() {
    endwin();
}

void NCurses::loop() {
    getch();
}




