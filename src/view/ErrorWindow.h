//
// Created by magupov on 01.11.18.
//

#ifndef ELF_EXPLORER_ERRORWINDOW_H
#define ELF_EXPLORER_ERRORWINDOW_H

#include <view/Widget.h>

class ErrorWindow : public Widget {

public:
    ErrorWindow(const std::string &error, int width, int height, int startx, int starty);
    virtual ~ErrorWindow();

    bool run();

protected:
    void render();
};


#endif //ELF_EXPLORER_ERRORWINDOW_H
