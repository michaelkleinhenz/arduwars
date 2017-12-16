#include "Arduboy.h"

#include "globals.h"
#include "bitmaps.h"
#include "levels.h"
#include "battle.h"

const uint8_t WINDOW_SIZE_X = 7;
const uint8_t WINDOW_SIZE_Y = 4;

unsigned char windowBuffer[28] = {
  0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1 
};
uint8_t mapId;
uint8_t cursorPosX;
uint8_t cursorPosY;

Battle::Battle() {
  // NOP
}

void Battle::drawTileAt(uint8_t x, uint8_t y, const uint8_t* bitmap) {
  arduboy.drawSlowXYBitmap(x*16, y*16, bitmap, 16, 16, 1);
}

void Battle::drawWindow() {
  for(uint8_t y=0; y<=4; y++) {
    for(uint8_t x=0; x<=7; x++) {
      uint8_t flatCoord = xyToFlatCoordinate(x, y, WINDOW_SIZE_X);
      if (windowBuffer[flatCoord]==0) 
        drawTileAt(x, y, tile_0);
      else
        drawTileAt(x, y, tile_1);
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

const unsigned char* Battle::getUnitMap() {
  if (mapId == 0) 
    return level_00_units;
  else if (mapId == 1)
    return level_01_units;
}

void Battle::updateWindow() {
  // based on the cursorX/Y on the map, the window is updated 

}

void Battle::show(uint8_t newMapId) {
  mapId = newMapId;
  if (newMapId == 0) {
    cursorPosX = 5;
    cursorPosY = 5;  
  }
  updateWindow();
  drawWindow();
}

// battle loop, returns true as long as battle is running
boolean Battle::loop() {
  return true;
}
