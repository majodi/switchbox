#include "menu.h"

void drawMenu() {
  // DEBUG_V("menuSubOffset: %d", menuSubOffset); DEBUG_V(" - "); DEBUG_V("menuSubPos: %d", menuSubPos); 
  // DEBUG_V("---------\n");
  u8g2.firstPage();
  do {
    // Serial.print(menuTopPos); Serial.print(" - ");
    u8g2.setFont(menuFont);
    drawTopMenu();
    if (menuActive == 0) {
      drawMenuInfo();
    } else {                          // LET OP: bij menu change reset rotary virtual naar laatste menu pos
      drawSubMenu();
    }
  } while ( u8g2.nextPage() );
}

void drawTopMenu() {
  if (menuActive == 0) {
    drawTopMenuScroll();
  }
  u8g2.setFont(menuFont);
  u8g2.setDrawColor(2);
  const byte centeredXPos = 64 - u8g2.getUTF8Width(menuMatrix[0][menuTopPos]) / 2;
  u8g2.drawStr(centeredXPos, 1 * menuFontHeight, menuMatrix[0][menuTopPos]);
}

void drawTopMenuScroll() {
  // menuTopPos is 0-based, first top menu item is index 0
  // only 1 topMenu (matrix row-index 0)
  u8g2.setFont(iconFont_arrow_2x);
  if ((menuTopPos + 1) > 1) {
    u8g2.drawGlyph(0, (0 * iconFont_arrow_2xHeight) + iconFont_arrow_2xHeight, ico_arrowLeft);
  };
  if ((menuTopPos + 1) < nrOfTopMenuItems) {
    u8g2.drawGlyph(128 - iconFont_arrow_2xWidth, (0 * iconFont_arrow_2xHeight) + iconFont_arrow_2xHeight, ico_arrowRight);
  }
}

void drawSubMenu() {
  drawSubMenuScroll();
  u8g2.setFont(menuFont);
  for (byte i = 0; i <= 2; i++) {
    u8g2.setDrawColor(2);
    u8g2.drawStr(2, topMargin + ((2 + i) * menuFontHeight), menuMatrix[menuTopPos + 1][menuSubPos + i]);
  }
}

void drawSubMenuScroll() {
  u8g2.setFont(iconFont_arrow_2x);
  if (menuSubPos > 0) {
    u8g2.drawGlyph(128 - iconFont_arrow_2xWidth, (1 * iconFont_arrow_2xHeight) + iconFont_arrow_2xHeight, ico_arrowUp);
  };
  if ((menuSubPos) < nrOfSubMenuItems - 3) {
    u8g2.drawGlyph(128 - iconFont_arrow_2xWidth, (3 * iconFont_arrow_2xHeight) + iconFont_arrow_2xHeight, ico_arrowDown);
  }
  u8g2.setFontMode(1);
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, topMargin + 2 + ((1 + menuSubOffset) * menuFontHeight), 128 - iconFont_arrow_2xWidth, menuFontHeight); //+2 pixels, +1 line (topmenu)
}

void drawMenuInfo() {
  u8g2.setFont(iconFont_embedded_6x);
  u8g2.drawGlyph(40, 64, pictogramsTopMenu[menuTopPos]);
}

void setMenuState() {
  // DEBUG_V("menuSubOffset: %d", menuSubOffset); DEBUG_V(" - "); DEBUG_V("menuSubPos: %d\n", menuSubPos); 
  if (rotaryPushed) {
    savMenuSubOffset = menuSubOffset; savMenuSubPos = menuSubPos; savRotaryVirtual = rotaryVirtual;
    action = menuActive != 0 ? menuSubPos + menuSubOffset : 0;
    menuActive = menuActive == 0 ? 1 : 0; // on select top menu (push), switch to sub menu else return to top menu
  }
  // DEBUG_V("menuActive: %d", menuActive); DEBUG_V(" en menuLastActive: %d\n", menuLastActive);
  if (menuActive != menuLastActive) { // on menu change, reset virtual to 0 (sub menu) or to last known top position
    rotaryVirtual = menuActive == 0 ? menuTopPos : 0;
  }
  menuLastActive = menuActive;
  if (menuActive == 0) { // react only when active
    rotaryVirtual = bound(rotaryVirtual, 0, nrOfTopMenuItems-1); // refresh position to position of last rotary spin
    // Serial.println(rotaryVirtual);
    menuTopPos = rotaryVirtual;
    nrOfSubMenuItems = nrOfItems[menuTopPos + 1]; // doesn't work with cpp: sizeof(menuMatrix[menuTopPos + 1]) / 4; // number of 4 byte pointers...
  } else {
    if (rotaryVirtual > 2 && rotaryVirtual < 127) {menuSubPos++; rotaryVirtual = 2;}; // over max, keep max but try to bump up view port
    if (rotaryVirtual > 127) {menuSubPos--; rotaryVirtual = 0;}; // under min (negative number), keep min but try to bump down view port
    menuSubOffset = rotaryVirtual;
    menuSubPos = bound(menuSubPos, 0, nrOfSubMenuItems - 3); // menuSubPos is top item in viewport of 3 lines and is 0-based. Max is nr-items - 3
  }
  // DEBUG_V("=============\n");
  // DEBUG_V("Menu Top Pos: %d\n", menuTopPos);
  // DEBUG_V("Menu Sub Pos: %d\n", menuSubPos);
  // DEBUG_V("Menu Sub off: %d\n", menuSubOffset);
  // DEBUG_V("Nr Of Sub: %d\n", nrOfSubMenuItems);
}
void restoreMenuBeforePush() {
  menuSubOffset = savMenuSubOffset; menuSubPos = savMenuSubPos; rotaryVirtual = savRotaryVirtual;
}

byte xCenter(byte strLength, byte fontWidth, byte lineWidth) {
  return ((lineWidth) / 2) - ((strLength / 2) * fontWidth);
}

byte bound(byte value, byte lower, byte upper) {
  // only positive values 0-127
  value = value > 127 ? (byte) 0 : value; // negative = 0
  value = value < lower ? lower : value;
  return value >= upper ? upper : value;
}
