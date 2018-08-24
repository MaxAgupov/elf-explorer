//
// Created by magupov on 10.08.18.
//

#include "App.h"
#include <view/NCurses.h>

#include <view/FileMenu.h>
#include <view/Window.h>

#include <string>

using namespace std;

App::App(int argc, char **argv) {

}

int App::run() {
    NCurses main_view;

    main_view.init();


    Window *win = new Window(main_view.screen_width(), main_view.screen_height(), 0, 0);

    FileMenu *menu = new FileMenu(main_view.screen_width()/2,
                        main_view.screen_height(),
                        main_view.screen_width()/4, 0);

    // control buttons
//    attron(A_REVERSE);
//    mvprintw(main_view.screen_height() - 1, 0,
//            string(main_view.screen_width(), ' ').c_str());
//    attroff(A_REVERSE);
    refresh();

    win->render();
    bool result = menu->run();
    if (result) {
        string chosen_filename = menu->getChosenFileName();
        win->render();
    }

    delete menu;
    refresh();
    main_view.loop();

    main_view.end();
    return 0;
}

