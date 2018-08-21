//
// Created by Maxim Agupov on 11.08.2018.
//

#include <algorithm>
#include "ListMenu.h"

#include <iostream>

using namespace std;

ListMenu::ListMenu(int width, int height, int startx, int starty)
 : Menu(width, height, startx, starty){
    first_visible_item = 0;
    max_visible_size = height - 3;
    visible_size = 0;
    highlighted = 0;

    chosen_item = full_list.end();
    keypad(menu, true);
}

void ListMenu::render() {
    int index = 0;
    for (auto it = full_list.begin(); it != full_list.end(); ++it, ++index) {
        if (index >= first_visible_item) {
            if (first_visible_item + highlighted == index) {
                wattron(menu, A_REVERSE);
            }
            preRenderItem(*it);
            mvwprintw(menu, index -first_visible_item + 1, 1, (*it)->getLabel(width-2).c_str());
            postRenderItem(*it);
            wattroff(menu, A_REVERSE);
        }
        if (index >= first_visible_item + visible_size - 1) {
            break;
        }
    }

    if (visible_size != max_visible_size) {
        for (int i = visible_size+1; i <= max_visible_size; ++i) {
            mvwprintw(menu, i, 1, string(width-2, ' ').c_str());
        }
    }

    // control buttons
    wattron(menu, A_REVERSE);
    mvwprintw(menu, height - 2, 1, (string ("<Enter>-Choose | F10-Exit") + string(width - 2 - 25, ' ')).c_str());
    wattroff(menu, A_REVERSE);
    Menu::render();
}

bool ListMenu::run() {
    bool result = false;
    bool exit = false;
    while (!exit) {
        render();
        switch(wgetch(menu)) {
            case KEY_UP:
                handleUp();
                break;
            case KEY_DOWN:
                handleDown();
                break;
            case '\n':
            case KEY_ENTER:
                result = handleEnter();
                if (result) {
                    exit = true;
                }
                break;
            case KEY_F(10):
                exit = true;
            default:
                break;
        }
    }
    return result;
}

void ListMenu::handleUp() {
    if (full_list.empty()) {
        first_visible_item = 0;
        highlighted = 0;
        return;
    }
    if (highlighted > 0) {
        highlighted--;
    } else if (first_visible_item > 0) {
        first_visible_item--;
    }
}

void ListMenu::handleDown() {
    if (full_list.empty()) {
        first_visible_item = 0;
        highlighted = 0;
        visible_size = 0;
        return;
    }
    if (highlighted < visible_size - 1 ) {
        highlighted++;
    } else if (first_visible_item + visible_size < full_list.size()) {
        first_visible_item++;
    }
}

void ListMenu::addItem(const string &label, ItemContent *item) {
    if (visible_size < max_visible_size) {
        visible_size++;
    }
    full_list.push_back(new ListMenuItem(label, item));
}

ItemContent *ListMenu::getChosenItem() const {
    int index = 0;
    for (auto it = full_list.begin(); it != full_list.end(); ++it, ++index) {
        if (index == first_visible_item + highlighted) {
            return (*it)->getContent();
        }
    }
    return nullptr;
}

ListMenu::~ListMenu() {
    cleanScreen();
}

void ListMenu::cleanScreen() {
    for_each(full_list.begin(), full_list.end(), [](ListMenuItem* item){
        delete item;
    });
    full_list.clear();
    first_visible_item = 0;
    highlighted = 0;
    visible_size = 0;
}

bool ListMenu::handleEnter() {
    return true;
}

void ListMenu::preRenderItem(ListMenuItem *item) {
}

void ListMenu::postRenderItem(ListMenuItem *item) {
}

void ListMenu::sortItems() {
    full_list.sort([](ListMenuItem* litem, ListMenuItem *ritem){
        return litem->getLabel().compare(ritem->getLabel()) < 0;
    });
}

ListMenuItem::ListMenuItem(const std::string &full_label, ItemContent *content)
    : full_label(full_label), content(content){
}
