#include "Arduboy2.h"
#include "globals.h"
#include "bitmaps.h"  
#include "cutscene.h"

Cutscene::Cutscene() {
  // NOP
}

void Cutscene::show(byte mapId) {
  arduboy.display();
}

// cutscene loop, returns true as long as cutscene is running
boolean Cutscene::loop() {
  return true;
}
