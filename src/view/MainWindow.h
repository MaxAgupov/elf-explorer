//
// Created by magupov on 21.08.18.
//

#ifndef ELF_EXPLORER_WINDOW_H
#define ELF_EXPLORER_WINDOW_H

#include <view/Widget.h>

class Analyser;
class ListPanel;

class MainWindow : public Widget {
public:
    MainWindow(int width, int height, int startx, int starty);
    virtual ~MainWindow();

    virtual bool run();
    virtual void render();

    void openFile(const std::string &fileName);

protected:
    void drawHeader();
    void drawButtons();

protected:
    std::string header;
    Analyser *analyser;
    ListPanel *leftPanel;
};


#endif //ELF_EXPLORER_WINDOW_H
