//
// Created by magupov on 21.08.18.
//

#include "Window.h"

#include <string>

using std::string;

Window::Window(int width, int height, int startx, int starty)
    : Widget (width, height, startx, starty){

}

Window::~Window() {

}

void Window::render() {
    drawFrame();
    for (int i = 1; i < height - 1; ++i) {
        drawLine(1, i, string(width-2, ' '));
    }
    Widget::render();
}

bool Window::run() {
    bool result = false;
    bool exit = false;
    while (!exit) {
        render();
        switch(getCh()) {
            case KEY_F(10):
                exit = true;
            default:
                break;
        }
    }
    return result;
}
