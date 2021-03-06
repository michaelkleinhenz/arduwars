#include "Arduboy2.h"
#include "levels.h"

static const Terrain terrains[] PROGMEM = {
  { "Valley",  0,  10 },
  { "Forest",  1,  20 },
  { "Mountains",  2,  30 },
 };
 
const uint8_t PROGMEM level_00_sizeX = 20;
const uint8_t PROGMEM level_00_sizeY = 20;
const unsigned char PROGMEM level_00_env[level_00_sizeY*level_00_sizeX] = {
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,26,15,15,15,15,15,
  15,15,15,15,28,15,15,26,15,15,15,28,15,15,15,15,15,28,15,15,
  15,26,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,26,
  15,15,15,1,49,15,15,26,15,15,36,15,26,15,15,26,15,15,15,15,
  15,28,15,2,50,15,15,15,15,15,15,15,15,15,15,15,35,15,15,15,
  15,15,15,3,51,15,15,15,26,15,15,15,15,15,36,15,15,15,28,15,
  15,15,15,15,15,15,36,15,35,15,15,26,15,15,15,15,15,15,15,15,
  15,15,28,15,15,15,15,15,15,15,15,15,15,15,15,26,15,15,28,15,
  15,15,15,15,26,15,28,15,36,15,15,15,15,36,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,35,15,15,15,15,15,15,15,15,15,
  15,26,15,15,15,15,15,15,15,15,15,15,15,28,15,35,26,15,15,36,
  15,15,15,35,15,15,15,26,15,15,28,15,15,15,15,26,28,15,15,15,
  15,15,36,15,15,36,15,15,15,15,15,15,26,15,15,15,28,15,36,15,
  15,15,15,15,15,15,15,15,15,36,15,15,15,15,15,36,15,15,15,15,
  15,15,15,28,15,15,35,15,15,15,28,15,15,15,15,15,15,15,15,15,
  15,26,15,15,15,15,15,26,15,15,15,15,26,15,15,15,35,15,15,15,
  15,15,15,28,15,15,15,28,15,15,15,15,15,15,15,15,15,26,15,36,
  15,15,15,15,15,15,36,36,15,15,15,15,15,36,15,15,15,15,15,15,
  15,15,35,15,36,15,15,15,15,26,15,36,15,35,15,28,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15
};
const unsigned char PROGMEM level_00_units[level_00_sizeY*level_00_sizeX] = {
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1
};

const uint8_t PROGMEM level_01_sizeX = 14;
const uint8_t PROGMEM level_01_sizeY = 8;
const unsigned char PROGMEM level_01_env[level_01_sizeY*level_01_sizeX] = {
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
};
const unsigned char PROGMEM level_01_units[level_01_sizeY*level_01_sizeX] = {
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
};
