//
// Created by magupov on 21.08.18.
//

#ifndef ELF_EXPLORER_MAINWINDOW_H
#define ELF_EXPLORER_MAINWINDOW_H

#include <string>

class DisplayManager {
public:
    DisplayManager();
    ~DisplayManager();

    void show();

protected:
    void chooseFile(std::string &chosen_file);

private:
    void initNcurses();
    void endNcurses();

    int screen_width() const;
    int screen_height() const;
};


#endif //ELF_EXPLORER_MAINWINDOW_H
