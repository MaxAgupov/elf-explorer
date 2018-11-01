//
// Created by magupov on 01.11.18.
//

#include "ErrorWindow.h"

ErrorWindow::ErrorWindow(const std::string &error, int width, int height, int startx, int starty)
: Widget(width, height, startx, starty) {

}

ErrorWindow::~ErrorWindow() {

}

bool ErrorWindow::run() {
    bool exit = false;
    while (!exit) {
        render();
        int ch = getCh();
        switch(ch) {
            default:
                exit = true;
                break;
        }
    }
    return true;
}

void ErrorWindow::render() {
    refresh();
}


