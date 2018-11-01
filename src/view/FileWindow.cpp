//
// Created by Maxim Agupov on 12.08.2018.
//

#include "FileWindow.h"
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <algorithm>

#include <iostream>

using namespace std;

using std::string;

FileWindow::FileWindow(int width, int height, int startx, int starty)
    : ListPanel(width, height, startx, starty) {
    size_t dir_size = 256;
    char *res_buf = nullptr;
    do {
        char c_dir[dir_size];
        res_buf = getcwd(c_dir, dir_size);
        if (res_buf != nullptr) {
            current_dir = c_dir;
        } else if (errno == EACCES) {
            // ERROR
            break;
        } else {
            dir_size <<= 1;
        }
    } while (res_buf == nullptr);

    if (!current_dir.empty()) {
        load_directory_content(current_dir);
    }
}

FileWindow::~FileWindow() {
    clearContent();
}

bool FileWindow::run() {
    bool result = false;
    bool exit = false;
    while (!exit) {
        render();
        int ch = getCh();
        ListPanel::processKeyboard(ch);
        switch(ch) {
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

void FileWindow::load_directory_content(string dir_name) {
    DIR *dir = opendir(dir_name.c_str());
    if (dir == NULL) {
        return;
    }
    struct dirent *ent;
    while ((ent = readdir (dir)) != NULL) {
        DirEntry *entry = new DirEntry;
        entry->name = ent->d_name;
        entry->type = ent->d_type;

        if (entry->name == ".") {
            continue;
        }
        content.push_back(entry);
    }
    closedir(dir);

    for (auto it = content.begin(); it != content.end(); ++it) {
        addItem((*it)->name, (*it));
    }
    sortItems();
}

bool FileWindow::handleEnter() {
    DirEntry *entry = dynamic_cast<DirEntry*>(getChosenItem());

    if (entry == nullptr) {
        return false;
    }

    if (entry->name == "..") {
        // go to the parent dir
        size_t pos = current_dir.rfind('/');
        if (pos != 0){
            current_dir = current_dir.substr(0, pos);
        } else {
            current_dir = "/";
        }
        clearContent();
        load_directory_content(current_dir);
    } else if (entry->type == DT_DIR) {
        // enter the chosen dir
        current_dir = current_dir + "/" + entry->name;
        clearContent();
        load_directory_content(current_dir);
    } else {
        return true;
    }

    return false;
}

void FileWindow::clearContent() {
    cleanScreen();
    for (auto it = content.begin(); it != content.end(); ++it) {
        delete (*it);
    }
    content.clear();
}

void FileWindow::preRenderItem(ListMenuItem *item) {
    DirEntry *entry = dynamic_cast<DirEntry*>(item->getContent());

    if (entry == nullptr) {
        return;
    }
    if (entry->type == DT_DIR) {
        onAttribute(A_BOLD);
    }
}

void FileWindow::postRenderItem(ListMenuItem *item) {
    offAttribute(A_BOLD);
}

void FileWindow::sortItems() {
    full_list.sort([](ListMenuItem* lv, ListMenuItem *rv) {
        if (lv->getLabel() == "..") {
            return true;
        }
        if (rv->getLabel() == "..") {
            return false;
        }
        DirEntry *lentry = dynamic_cast<DirEntry*>(lv->getContent());
        DirEntry *rentry = dynamic_cast<DirEntry*>(rv->getContent());

        if (lentry->type == rentry->type) {
            return lv->getLabel().compare(rv->getLabel()) < 0;
        } else {
            if (lentry->type == DT_DIR) {
                return true;
            } else if (rentry->type == DT_DIR) {
                return false;
            } else {
                return lv->getLabel().compare(rv->getLabel()) < 0;
            }
        }

    });
}

std::string FileWindow::getChosenFileName() const {
    DirEntry *entry = dynamic_cast<DirEntry*>(getChosenItem());

    if (entry == nullptr) {
        return std::string();
    }

    return current_dir + "/" + entry->name;
}

void FileWindow::render() {
    ListPanel::render();

    // control buttons
    onAttribute(A_REVERSE);
    string descr = "<Enter>-Choose | <F10>-Exit";
    drawLine(1, height - 1, (descr + string(width - 2 - descr.size(), ' ')));
    offAttribute(A_REVERSE);

    Widget::refresh();
}

