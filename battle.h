#ifndef BATTLEMAP_H
#define BATTLEMAP_H

class Battle
{
  public:
    Battle();
    void show(uint8_t mapId);
    boolean loop();
  private:
    const unsigned char* getLevelMap();
    const unsigned char* getUnitMap();
    void updateWindow();
    void drawWindow();
    void drawTileAt(uint8_t x, uint8_t y, const uint8_t* bitmap);
    uint8_t xyToFlatCoordinate(uint8_t x, uint8_t y, uint8_t sizeX);
};

#endif
