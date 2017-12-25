#ifndef LEVELS_H
#define LEVELS_H

#define MAX_NAME_LENGTH 10

typedef struct Terrain {
	char name[MAX_NAME_LENGTH];				
	uint8_t spriteId;
	uint8_t moveRestricted;
} Terrain;

extern const Terrain terrains[];

extern const uint8_t level_00_sizeX;
extern const uint8_t level_00_sizeY;
extern const unsigned char level_00_env[];
extern const unsigned char level_00_units[];

extern const uint8_t level_01_sizeX;
extern const uint8_t level_01_sizeY;
extern const unsigned char level_01_env[];
extern const unsigned char level_01_units[];

#endif
