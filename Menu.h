#ifndef MENU_H
#define MENU_H
#include <Arduino.h>

//Raw pointers are used. Carefully look for memory leaks
 
class Menu {
public:

    bool dynamic;
    String name;
    Menu* parent;
    Menu* children[6]; // Static array of 10 pointers to Menu
    int childrenCount=0;

    String content[6];
    
    uint8_t selected=0;
    
    Menu(String name, Menu* parent = nullptr, bool dynamic=false);

    void addChild(Menu* child); 

    Menu* goToChild(int index); 
    Menu* goToParent();

    void addContentFromChildren();
    void addContent(String content);

    void setDynamic(bool dynamic);


};




#endif
/*
Usage:
   / Create root menu
Menu root("Root");

// Create first level submenus
Menu subMenu1("SubMenu1", &root);
Menu subMenu2("SubMenu2", &root);

// Add first level submenus to root
root.addChild(&subMenu1);
root.addChild(&subMenu2);

// Create second level submenu
Menu subSubMenu1("SubSubMenu1", &subMenu1);

// Add second level submenu to first submenu
subMenu1.addChild(&subSubMenu1);

// Now you can navigate through the menus
Menu* currentMenu = &root;
currentMenu = currentMenu->goToChild(0); // Go to SubMenu1
currentMenu = currentMenu->goToChild(0); // Go to SubSubMenu1
currentMenu = currentMenu->goToParent(); // Go back to SubMenu1
currentMenu = currentMenu->goToParent(); // Go back to Root
*/
