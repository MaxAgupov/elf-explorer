//
// Created by Maxim Agupov on 11.08.2018.
//

#ifndef ELF_EXPLORER_SIMPLELISTMENU_H
#define ELF_EXPLORER_SIMPLELISTMENU_H

#include <view/Widget.h>
#include <string>
#include <vector>
#include <list>

class ItemContent;

class ItemContent {
public:
    ItemContent() {}
    virtual ~ItemContent(){}
};

class ListMenuItem {
public:
    ListMenuItem(const std::string &full_label, ItemContent *content);

    virtual std::string getLabel() const {
        return full_label;
    }

    virtual std::string getLabel(size_t size) const {
        if (full_label.size() < size) {
            return full_label.substr(0, size) + std::string (size - full_label.size(), ' ');
        } else if (full_label.size() > size) {
            return full_label.substr(0, size - 1) + '>';
        } else {
            return full_label;
        }
    }

    ItemContent* getContent() const {
        return content;
    }

private:
    std::string full_label;
    ItemContent *content;
};

class ListPanel : public Widget {
public:
    ListPanel(int width, int height, int startx, int starty);
    virtual ~ListPanel();

    ItemContent *getChosenItem() const;

    void addItem(const std::string &label, ItemContent *item);

    virtual void handleUp();

    virtual void handleDown();

    virtual bool handleEnter();

    virtual void sortItems();

    virtual void preRenderItem(ListMenuItem* item);

    virtual void postRenderItem(ListMenuItem* item);

    void cleanScreen();

    void render();

    void processKeyboard(int Key);

protected:
    std::list<ListMenuItem*> full_list;
    std::list<ListMenuItem*>::iterator chosen_item;

    int first_visible_item;
    int max_visible_size;
    int visible_size;
    int highlighted;
};


#endif //ELF_EXPLORER_SIMPLELISTMENU_H
