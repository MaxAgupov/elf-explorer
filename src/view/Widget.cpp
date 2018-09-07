//
// Created by magupov on 21.08.18.
//

#include "Widget.h"


Widget::Widget(int width, int height, int startx, int starty)
        : width(width), height(height), startx(startx), starty(starty) {
    widget = newwin(height, width, starty, startx);
//    drawFrame();
    keypad(widget, true);
}

Widget::~Widget() {
    delwin(widget);
}

void Widget::render() {
    wrefresh(widget);
}

void Widget::onAttribute(unsigned long attr) {
    wattron(widget, attr);
}

void Widget::offAttribute(unsigned long attr) {
    wattroff(widget, attr);
}

void Widget::drawLine(int x_pos, int y_pos, const std::string &line) {
    mvwprintw(widget, y_pos, x_pos, line.c_str());
}

int Widget::getCh() {
    return getch();
//    return wgetch(widget);
}

void Widget::drawFrame() {
    box(widget, 0, 0);
}

