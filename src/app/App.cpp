//
// Created by magupov on 10.08.18.
//

#include "App.h"

#include <view/DisplayManager.h>

#include <string>

using namespace std;

App::App(int argc, char **argv) {

}

int App::run() {

    DisplayManager mng;
    mng.show();

    return 0;
}

