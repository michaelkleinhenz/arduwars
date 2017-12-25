#include <avr/pgmspace.h>

#include "Arduboy2.h"
#include "Sprites.h"

#include "progmem_read.h"
#include "globals.h"
#include "bitmaps.h"
#include "levels.h"
#include "units.h"
#include "battle.h"

const uint8_t WINDOW_SIZE_X = 7;
const uint8_t WINDOW_SIZE_Y = 4;
const uint8_t ANIMATION_DELAY = 10;

// the window buffer for map and unit contents
unsigned char windowBuffer[28] = {
  0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1 
};
// top left window is the following position in the map
uint8_t windowPosX;
uint8_t windowPosY;
// the current mapId
uint8_t mapId = 0;
// the position of the cursor in the window
uint8_t windowCursorPosX;
uint8_t windowCursorPosY;
// the current cursor animation frame
uint8_t cursorAnimState = 0;

Battle::Battle() {
  // NOP
}

void Battle::drawTileAt(uint8_t x, uint8_t y, uint8_t tileId) {
  sprites.drawOverwrite(x*16, y*16, tileSheet, tileId);
}

void Battle::drawWindow() {
  for(uint8_t y=0; y<WINDOW_SIZE_Y; y++) {
    for(uint8_t x=0; x<WINDOW_SIZE_X; x++) {
      uint8_t flatCoord = xyToFlatCoordinate(x, y, WINDOW_SIZE_X);
      drawTileAt(x, y, windowBuffer[flatCoord]);
    }
  }
  arduboy.display();
}

uint8_t Battle::xyToFlatCoordinate(uint8_t x, uint8_t y, uint8_t sizeX) {
  return y*sizeX+x;
}

const unsigned char* Battle::getLevelMap() {
  if (mapId == 0) 
    return level_00_env;
  else if (mapId == 1)
    return level_01_env;
}

const uint8_t Battle::getLevelXSize() {
  if (mapId == 0) 
    return level_00_sizeX;
  else if (mapId == 1)
    return level_01_sizeX;
}

const uint8_t Battle::getLevelYSize() {
  if (mapId == 0) 
    return level_00_sizeY;
  else if (mapId == 1)
    return level_01_sizeY;
}

const uint8_t* Battle::getUnitMap() {
  if (mapId == 0) 
    return level_00_units;
  else if (mapId == 1)
    return level_01_units;
}


void Battle::checkKeys() {
  if (arduboy.pressed(LEFT_BUTTON)) {
    if ((windowCursorPosX == 1) && (windowPosX > 0)) {
      // window moving left
      windowPosX--;
    } else if (windowCursorPosX > 0)
      windowCursorPosX--;
  } else if (arduboy.pressed(RIGHT_BUTTON)) {
    if ((windowCursorPosX == WINDOW_SIZE_X - 2) && (windowPosX < getLevelXSize() - WINDOW_SIZE_X)) {
      // window moving right
      windowPosX++;
    } else if (windowCursorPosX < WINDOW_SIZE_X - 1) {
      // cursor moving right
      windowCursorPosX++;
    }
  } else if (arduboy.pressed(UP_BUTTON)) {
    if ((windowCursorPosY == 1) && (windowPosY > 0)) {
      // window moving up
      windowPosY--;
    } else if (windowCursorPosY > 0) {
      // cursor moving up
      windowCursorPosY--;
    }
  } else if (arduboy.pressed(DOWN_BUTTON)) {      
    if ((windowCursorPosY == WINDOW_SIZE_Y - 2) && (windowPosY < getLevelYSize() - WINDOW_SIZE_Y)) {
      // window moving down
      windowPosY++;      
    } else if (windowCursorPosY < WINDOW_SIZE_Y - 1) {
      // cursor moving down
      windowCursorPosY++;
    }      
  }
}

void Battle::updateWindow() {
  // update the window with the content of the map based on windowPosX/windowPosY
  for(uint8_t y=0; y<WINDOW_SIZE_Y; y++) {
    for(uint8_t x=0; x<WINDOW_SIZE_X; x++) {
      uint8_t windowFlatCoord = xyToFlatCoordinate(x, y, WINDOW_SIZE_X);
      // TODO: check bounds of map here
      uint8_t mapFlatCoord = xyToFlatCoordinate(windowPosX + x, windowPosY + y, getLevelXSize());
      windowBuffer[windowFlatCoord] = pgm_read_byte_near(getLevelMap() + mapFlatCoord); 
    }
  }
}

void Battle::drawCursor() {
  if (cursorAnimState >= 3)
    cursorAnimState = 0;
  else 
    cursorAnimState = cursorAnimState + 1;
  sprites.drawPlusMask(windowCursorPosX * 16, windowCursorPosY * 16, cursor_plus_mask, cursorAnimState);
}



void Battle::show(uint8_t newMapId) {
  mapId = newMapId;
  windowCursorPosX = 1;
  windowCursorPosY = 1;  
  windowPosX = 0;
  windowPosY = 0;

      char buffer[250];
      //sprintf(buffer, "windowX: %i - windowY: %i - levelXSize: %i - levelYSize: %i - cursorX: %i - cursorY: %i\n", windowPosX, windowPosY, getLevelXSize(), getLevelYSize(), windowCursorPosX, windowCursorPosY);
      Unit unit0;
      PROGMEM_readAnything(&units[0], unit0);
      sprintf(buffer, "title: %s - desc: %s - val0: %i - val1: %i - val3: %i\n", unit0.name, unit0.description, unit0.attack, unit0.defend, unit0.spriteId);
      Serial.print(buffer);

}

// battle loop, returns true as long as battle is running
boolean Battle::loop() {
  arduboy.pollButtons();
  // we only do animation every ANIMATION_DELAY-th frame
  if (arduboy.everyXFrames(ANIMATION_DELAY)) {
    // do actual game loop
    checkKeys();
    updateWindow();
    drawWindow();
    drawCursor();
    arduboy.display();
  }
  return true;
}
