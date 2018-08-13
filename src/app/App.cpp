//
// Created by magupov on 10.08.18.
//

#include "App.h"
#include <view/NCurses.h>

#include <view/FileMenu.h>

#include <string>

using namespace std;

App::App(int argc, char **argv) {

}

int App::run() {
    NCurses main_view;


    main_view.init();

    FileMenu *menu = new FileMenu(main_view.screen_width()/2,
                        main_view.screen_height(),
                        main_view.screen_width()/4, 0);

    // control buttons
    attron(A_REVERSE);
    mvprintw(main_view.screen_height() - 1, 0,
            string(main_view.screen_width(), ' ').c_str());
    attroff(A_REVERSE);
    refresh();

    bool result = menu->run();

    delete menu;
    refresh();
    main_view.loop();


    main_view.end();
    return 0;
}

