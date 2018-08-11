//
// Created by magupov on 10.08.18.
//

#include "App.h"
#include <view/NCurses.h>

App::App(int argc, char **argv) {

}

int App::run() {
    NCurses main_view;

    main_view.init();

    main_view.loop();


    main_view.end();
    return 0;
}

