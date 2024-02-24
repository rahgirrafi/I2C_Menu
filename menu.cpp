#include<Menu.h>
#include<Arduino.h>

Menu::Menu(String name, Menu* parent, bool dynamic)
    : name(name), parent(parent), childrenCount(0) {
    for(int i = 0; i < 6; i++) {
        children[i] = nullptr; // Initialize all pointers to nullptr
    }
    this->dynamic = dynamic;
}

void Menu::setDynamic(bool dynamic) {
    this->dynamic = dynamic;
}

void Menu::addChild(Menu* child) {
    if(childrenCount < 6) {
        children[childrenCount++] = child;
    }
} 

Menu* Menu::goToChild(int index) {
    if (index >= 0 && index < childrenCount) {
        return children[index];
    }
    return nullptr;
}

Menu* Menu::goToParent() {
    return parent;
}

void Menu::addContentFromChildren() {
    for(int i = 0; i < childrenCount; i++) {
        content[i] = children[i]->name;
    }
}

void Menu::addContent(String content) {
    this->content[childrenCount] = content;
    childrenCount++;
}