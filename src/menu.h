#ifndef MENU_H
#define MENU_H 1

#include "constants.h"

void drawMenu();
void setMenuState();
void restoreMenuBeforePush();
void drawTopMenu();
void drawMenuInfo();
void drawSubMenu();
void drawTopMenuScroll();
void drawSubMenuScroll();
byte bound(byte value, byte lower, byte upper);

#endif