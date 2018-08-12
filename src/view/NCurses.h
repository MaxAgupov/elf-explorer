//
// Created by max on 10.08.18.
//

#ifndef ELF_EXPLORER_NCURSES_H
#define ELF_EXPLORER_NCURSES_H


class NCurses {

public:
    NCurses();

    void init();

    void loop();

    void end();

    int screen_width();
    int screen_height();

};


#endif //ELF_EXPLORER_NCURSES_H
