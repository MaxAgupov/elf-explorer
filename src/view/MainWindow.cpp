//
// Created by magupov on 21.08.18.
//

#include "MainWindow.h"

#include <string>

#include <format/Analyser.h>
#include <format/FormatFactory.h>
#include <view/ListPanel.h>

using std::string;

MainWindow::MainWindow(int width, int height, int startx, int starty)
    : Widget (width, height, startx, starty), analyser(nullptr) {
    leftPanel = new ListPanel(width/2-2, height-2, startx+1, starty+1);
}

MainWindow::~MainWindow() {
    delete leftPanel;
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
void MainWindow::render() {
    drawFrame();
    drawHeader();

    drawButtons();

    Widget::render();
    leftPanel->render();
}

void MainWindow::drawButtons() {
    // Buttons description
    onAttribute(A_REVERSE);
    string descr = "<F2>-Open File | <F10>-Exit";
    drawLine(1, height - 1, (descr + string(width - 2 - descr.size(), ' ')));
    offAttribute(A_REVERSE);
}

bool MainWindow::run() {
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

void MainWindow::openFile(const std::string &fileName) {
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
    if (analyser) {
        std::vector<string> content;
        analyser->getHeaderList(content);
        leftPanel->cleanScreen();
        for (auto it = content.begin(); it != content.end(); ++it) {
            leftPanel->addItem(*it, nullptr);
        }
    } else {
        header = "Format isn't supported";
    }
}

void MainWindow::drawHeader() {
    if (!header.empty()) {
        drawLine(1, 0, header.substr(0, width-2));
    }
}

void MainWindow::processKeyboard(int Key) {
    leftPanel->processKeyboard(Key);
    switch(Key) {
        default:
            break;
    }
}
