
#include "Arduboy.h"
#include "globals.h"
#include "bitmaps.h"
#include "levels.h"
#include "display.h"

// declare globals
Arduboy arduboy;  

// locals
boolean start=false;

#include "pins_arduino.h" // Arduino pre-1.0 needs this

void intro()
{
  for(int i = -8; i < 28; i = i + 2)
  {
    arduboy.clear();
    arduboy.setCursor(46, i);
    arduboy.print("ARDUBOY");
    arduboy.display();
  }

  arduboy.tunes.tone(987, 160);
  delay(160);
  arduboy.tunes.tone(1318, 400);
  delay(2000);
}

/*
 arduboy.clear();
 arduboy.pressed(RIGHT_BUTTON)
 arduboy.drawRect(xPaddle, 63, 11, 1, 0);
 arduboy.pressed(A_BUTTON)
 arduboy.pressed(B_BUTTON);
 arduboy.drawPixel(xb,   yb,   0);
 (char)EEPROM.read(address + (5*i) + 2);
 EEPROM.write(address + (5*j) + 2, initials[0]);
 arduboy.setCursor(0,0);
 arduboy.setTextSize(2);
 arduboy.print("ARAKNOID");
*/

boolean pollFireButton(int n) {
  for(int i = 0; i < n; i++) {
    delay(15);
    byte pad = arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON);
    if (pad==1) {
      return true;
    }
  }
  return false;
}

boolean titleScreen() {
  arduboy.clear();
  arduboy.drawSlowXYBitmap(0, 0, title, 128, 64, 1);
  arduboy.display();
  if (pollFireButton(25)) {
    return true;
  }
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.display();
  intro();
}

void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  drawMap();
/*
  while (!start) {
    start = titleScreen();
  }
*/
  arduboy.display();
}


