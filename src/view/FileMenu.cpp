//
// Created by Maxim Agupov on 12.08.2018.
//

#include "FileMenu.h"
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

using std::string;

FileMenu::FileMenu(int width, int height, int startx, int starty)
    : Menu(width, height, startx, starty) {
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
}

FileMenu::~FileMenu() {

}

bool FileMenu::run() {
    return false;
}

void FileMenu::render() {
    Menu::render();
}

void FileMenu::load_directory_content(string dir_name) {


}
