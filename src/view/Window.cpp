//
// Created by magupov on 21.08.18.
//

#include "Window.h"

#include <string>

#include <format/Analyser.h>
#include <format/FormatFactory.h>

using std::string;

Window::Window(int width, int height, int startx, int starty)
    : Widget (width, height, startx, starty), analyser(nullptr) {

}

Window::~Window() {
    if (analyser) {
        delete analyser;
    }
}

/*
 * +------------
 * |    Header
 * +------------
 * |    Panels
 * |
 * |
 * +------------
 * |    Buttons description
 * +------------
 */
void Window::render() {
    drawFrame();
    if (!header.empty()) {
        drawLine(1, 0, header.substr(0, width-2));
    }

    if (analyser) {
        std::vector<std::string> content;
        analyser->getHeaderList(content);
        int index = 1;
        for (auto it = content.begin(); it != content.end(); ++it, ++index) {
            drawLine(1, index, *it + string(width - 2 - it->size(), ' ') );
        }
        for (int i = index; i < height - 1; ++i) {
            drawLine(1, i, string(width-2, ' '));
        }
    } else {
        for (int i = 1; i < height - 1; ++i) {
            drawLine(1, i, string(width-2, ' '));
        }
    }

    // Buttons description
    onAttribute(A_REVERSE);
    string descr = "<F2>-Open File | <F10>-Exit";
    drawLine(1, height - 1, (descr + string(width - 2 - descr.size(), ' ')));
    offAttribute(A_REVERSE);

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
                result = true;
                break;
            default:
                break;
        }
    }
    return result;
}

void Window::openFile(const std::string &fileName) {
    if (fileName.empty()) {
        header = "Need to choose file";
        return;
    }
    header = fileName;

    if (analyser) {
        delete analyser;
        analyser = nullptr;
    }
    analyser = FormatFactory::createAnalyser(fileName);
    if (analyser == nullptr) {
        header = "Format isn't supported";
    }
}
