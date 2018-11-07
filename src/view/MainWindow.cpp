//
// Created by magupov on 21.08.18.
//

#include "MainWindow.h"

#include <string>

#include <format/Analyser.h>
#include <format/FormatFactory.h>
#include <view/ListPanel.h>
#include <view/ErrorWindow.h>

using std::string;

MainWindow::MainWindow(int width, int height, int startx, int starty)
    : Widget (width, height, startx, starty), analyser(nullptr) {
    leftPanel = new ListPanel(width/2-1, height-2, startx+1, starty+1);
    rightPanel = new ListPanel(width/2-1, height-2, startx+1+width/2, starty+1);
    tabLoop.push_back(leftPanel);
    tabLoop.push_back(rightPanel);
    currentTabIt = tabLoop.begin();
}

MainWindow::~MainWindow() {
    tabLoop.clear();
    delete leftPanel;
    delete rightPanel;
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
    Widget::refresh();
    leftPanel->render();
    rightPanel->render();

}

void MainWindow::drawButtons() {
    // Buttons description
    onAttribute(A_REVERSE);
    string descr = "<F2>-Open File | <F10>-Exit";
    drawLine(1, height - 1, (descr + string(width - 2 - descr.size(), ' ')));
    offAttribute(A_REVERSE);
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
        std::string error = analyser->getHeaderList(content);
        if (error.empty()) {
            leftPanel->cleanScreen();
            for (auto it = content.begin(); it != content.end(); ++it) {
                leftPanel->addItem(*it, nullptr);
            }
        } else {
            auto errorWindow = new ErrorWindow(error, 100, 5, 10, 10);
            errorWindow->run();
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
    if (Key == '\t') {
        if ( ++currentTabIt == tabLoop.end()) {
            currentTabIt = tabLoop.begin();
        }
    }
    (*currentTabIt)->processKeyboard(Key);
    switch(Key) {
        default:
            break;
    }
}
