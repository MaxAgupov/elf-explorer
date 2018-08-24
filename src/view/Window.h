//
// Created by magupov on 21.08.18.
//

#ifndef ELF_EXPLORER_WINDOW_H
#define ELF_EXPLORER_WINDOW_H

#include <view/Widget.h>

class Window : public Widget {
public:
    Window(int width, int height, int startx, int starty);
    virtual ~Window();

    virtual bool run();
    virtual void render();

};


#endif //ELF_EXPLORER_WINDOW_H
