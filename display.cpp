#include "Arduboy.h"
#include "globals.h"
#include "display.h"
#include "bitmaps.h"

const unsigned int COLUMNS = 7; 
const unsigned int ROWS = 4;  

unsigned char mapBuffer[4][7] = {
  { 0, 1, 0, 1, 0, 1, 0 },
  { 1, 0, 1, 0, 1, 0, 1 },
  { 0, 1, 0, 1, 0, 1, 0 },
  { 1, 0, 1, 0, 1, 0, 1 }
};

void drawTileAtGrid(byte x, byte y, const uint8_t* bitmap) {
  arduboy.drawSlowXYBitmap(x*16, y*16, bitmap, 16, 16, 1);
}

void drawMap() {
  for(int y=0; y<=ROWS; y++) {
    for(int x=0; x<=COLUMNS; x++) {
      if (mapBuffer[y][x]==0) 
        drawTileAtGrid(x, y, tile_0);
      else
        drawTileAtGrid(x, y, tile_1);
    }
  }
  arduboy.display();
}

/*
void drawMap(unsigned char level[][7]) {
  for(int y=0; y<=ROWS; y++) {
    for(int x=0; x<=COLUMNS; x++) {
      if (pgm_read_byte(&(level_1[y][x]))==0) 
        drawTileAtGrid(x, y, tile_0);
      else
        drawTileAtGrid(x, y, tile_1);
    }
  }
  arduboy.display();
}
*/
