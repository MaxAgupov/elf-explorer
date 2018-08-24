//
// Created by max on 10.08.18.
//

#include <ncurses.h>

#include "NCurses.h"


NCurses::NCurses() {
    init();
}

NCurses::~NCurses() {
    end();
}

void NCurses::init() {
    initscr();
    noecho();
    cbreak();
    raw();
    curs_set(0);
    keypad(stdscr, true);

    refresh();
}

void NCurses::end() {
    endwin();
}

void NCurses::loop() {

    getch();
}

int NCurses::screen_width() {
    return COLS;
}

int NCurses::screen_height() {
    return LINES;
}




