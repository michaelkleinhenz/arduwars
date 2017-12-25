#ifndef BATTLEMAP_H
#define BATTLEMAP_H

class Battle
{
  public:
    Battle();
    void show(uint8_t mapId);
    boolean loop();
  private:
    const uint8_t getLevelXSize();
    const uint8_t getLevelYSize();
    const uint8_t* getLevelMap();
    const unsigned char* getUnitMap();
    void checkKeys();
    void updateWindow();
    void drawWindow();
    void drawCursor();
    void drawTileAt(uint8_t x, uint8_t y, uint8_t tileId);
    uint8_t xyToFlatCoordinate(uint8_t x, uint8_t y, uint8_t sizeX);
};

#endif
