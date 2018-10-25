//
// Created by magupov on 21.08.18.
//

#ifndef ELF_EXPLORER_WIDGET_H
#define ELF_EXPLORER_WIDGET_H

#include <ncurses.h>
#include <string>

class Widget {
public:
    Widget(int width, int height, int startx, int starty);

    virtual ~Widget();

    void refresh();

    void onAttribute(unsigned long attr);
    void offAttribute(unsigned long attr);

    void drawLine(int x_pos, int y_pos, const std::string &line);

    void drawFrame();

    int getCh();

protected:
    int width;
    int height;
    int startx;
    int starty;

private:
    WINDOW *widget;

};


#endif //ELF_EXPLORER_WIDGET_H
