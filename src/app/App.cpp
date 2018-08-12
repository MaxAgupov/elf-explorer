//
// Created by magupov on 10.08.18.
//

#include "App.h"
#include <view/NCurses.h>

#include <view/ListMenu.h>

#include <string>

using namespace std;

App::App(int argc, char **argv) {

}

int App::run() {
    NCurses main_view;


    main_view.init();

    ListMenu *menu = new ListMenu(main_view.screen_width()/2,
                        main_view.screen_height(),
                        main_view.screen_width()/4, 0);

    for(int i = 0; i < 100; ++i) {
        menu->addItem("line " + to_string(i), nullptr);
    }

    // control buttons
    attron(A_REVERSE);
    mvprintw(main_view.screen_height() - 1, 0,
            string(main_view.screen_width(), ' ').c_str());
    attroff(A_REVERSE);
    refresh();
    bool result = menu->run();
//    if (result) {
//        string res_item = menu->getChosenValue();
//        mvprintw(0, 0, res_item.c_str());
//    }
    // loop
    // handle event
    // render windows
    // wait action from user
    delete menu;
    refresh();
    main_view.loop();


    main_view.end();
    return 0;
}

