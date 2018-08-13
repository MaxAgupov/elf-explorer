//
// Created by Maxim Agupov on 12.08.2018.
//

#include "FileMenu.h"
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <algorithm>

#include <iostream>

using namespace std;

using std::string;

FileMenu::FileMenu(int width, int height, int startx, int starty)
    : ListMenu(width, height, startx, starty) {
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

FileMenu::~FileMenu() {
    clearContent();
}

bool FileMenu::run() {

    bool res = ListMenu::run();
    return res;
}

void FileMenu::render() {
    ListMenu::render();
}

void FileMenu::load_directory_content(string dir_name) {
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
}

bool FileMenu::handleEnter() {
    DirEntry *entry = dynamic_cast<DirEntry*>(getChosenItem());

    if (entry == nullptr) {
        return false;
    }

    if (entry->name == "..") {
        size_t pos = current_dir.rfind('/');
        if (pos != 0){
            current_dir = current_dir.substr(0, pos);
        } else {
            current_dir = "/";
        }
        clearContent();
        load_directory_content(current_dir);
    } else if (entry->type == DT_DIR){
        current_dir = current_dir + "/" + entry->name;
        clearContent();
        load_directory_content(current_dir);
    }

    return false;
}

void FileMenu::clearContent() {
    cleanScreen();
    for (auto it = content.begin(); it != content.end(); ++it) {
        delete (*it);
    }
    content.clear();
}

void FileMenu::preRenderItem(ListMenuItem *item) {
    DirEntry *entry = dynamic_cast<DirEntry*>(item->getContent());

    if (entry == nullptr) {
        return;
    }
    if (entry->type == DT_DIR) {
        wattron(menu, A_BOLD);
    }
}

void FileMenu::postRenderItem(ListMenuItem *item) {
    wattroff(menu, A_BOLD);
}
