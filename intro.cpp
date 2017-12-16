#include "Arduboy.h"
#include "globals.h"
#include "bitmaps.h"  
#include "intro.h"

Intro::Intro() {
  // NOP
}

// waits for button or given timeout
boolean Intro::waitForButton(int n) {
  for(int i = 0; i < n; i++) {
    delay(15);
    byte pad = arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON);
    if (pad==1) {
      return true;
    }
  }
  return false;
}

void Intro::show() {
  arduboy.clear();
  arduboy.drawSlowXYBitmap(0, 0, title, 128, 64, 1);
  arduboy.display();
}

// cutscene loop, returns true as long as cutscene is running
boolean Intro::loop() {
  waitForButton(25);
  arduboy.clear();
  return false;
}
