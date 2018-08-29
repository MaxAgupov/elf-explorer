//
// Created by magupov on 21.08.18.
//

#ifndef ELF_EXPLORER_MAINWINDOW_H
#define ELF_EXPLORER_MAINWINDOW_H

#include <string>

class NCurses;


class DisplayManager {
public:
    DisplayManager();
    ~DisplayManager();

    void show();

protected:
    void chooseFile(std::string &chosen_file);


private:
    NCurses *ncurses;
    bool is_shown;
};


#endif //ELF_EXPLORER_MAINWINDOW_H
