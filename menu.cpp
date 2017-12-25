#include "Arduboy2.h"
#include "globals.h"
#include "bitmaps.h"  
#include "menu.h"

Menu::Menu() {
  // NOP
}

void Menu::show() {
  arduboy.display();
}

// cutscene loop, returns -1 as long as menu is running
// returns id of menu item selected
byte Menu::loop() {
  return true;
}
