//
// Created by Maxim Agupov on 11.08.2018.
//

#include "ListMenu.h"

using namespace std;

ListMenu::ListMenu(int width, int height, int startx, int starty)
 : Menu(width, height, startx, starty){
    first_visible_item = 0;
    visible_size = height - 3;
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
            mvwprintw(menu, index -first_visible_item + 1, 1, (*it)->getLabel(width-2).c_str());
            wattroff(menu, A_REVERSE);
        }
        if (index >= first_visible_item + visible_size - 1) {
            break;
        }
    }

    // control buttons
    wattron(menu, A_REVERSE);
    mvwprintw(menu, height - 2, 1, string(width - 2, ' ').c_str());
    wattroff(menu, A_REVERSE);
    Menu::render();

}

bool ListMenu::run() {
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
            case 'q':
                exit = true;
            default:
                break;
        }
    }
    return true;
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
        return;
    }
    if (highlighted < visible_size - 1) {
        highlighted++;
    } else if (first_visible_item + visible_size < full_list.size()) {
        first_visible_item++;
    }
}

void ListMenu::addItem(const string &label, ItemContent *item) {
    full_list.push_back(new ListMenuItem(label, item));
    full_list.sort([](ListMenuItem* litem, ListMenuItem *ritem){
        return litem->getLabel().compare(ritem->getLabel()) < 0;
    });
}

ItemContent *ListMenu::getChosenItem() {
    return (chosen_item != full_list.end()) ? (*chosen_item)->getContent() : nullptr;
}

ListMenu::~ListMenu() {
    for_each(full_list.begin(), full_list.end(), [](ListMenuItem* item){
        delete item;
    });
    full_list.clear();
}

ListMenuItem::ListMenuItem(const std::string &full_label, ItemContent *content)
    : full_label(full_label), content(content){
}
