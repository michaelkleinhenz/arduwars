#ifndef UNITS_H
#define UNITS_H

#define MAX_DESCRIPTION_LENGTH 32
#define MAX_NAME_LENGTH 10

typedef struct Unit {
	char name[MAX_NAME_LENGTH];				
	uint8_t spriteId;
	uint8_t attack;
	uint8_t defend;
	uint8_t moveRangeMin;
	uint8_t moveRangeMax;
	uint8_t weaponRangeMin;
	uint8_t weaponRangeMax;
	char description[MAX_DESCRIPTION_LENGTH];	
} Unit;

extern const Unit units[];

typedef struct UnitInstance {
  Unit baseUnit;
  uint8_t life;
  uint8_t ammo;
  uint8_t mapPosX;
  uint8_t mapPosY;
  bool playerUnit;
} UnitInstance;

#endif
