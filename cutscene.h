#ifndef CUTSCENE_H
#define CUTSCENE_H

//#define ARDBITMAP_SBUF arduboy.getBuffer()
#define ARDBITMAP_SBUF arduboy.sBuffer
#include <ArdBitmap.h>

// the ticks the animation takes
const float ANIM_SPEED = 32;

const bool SIDE_LEFT = false;
const bool SIDE_RIGHT = true;
const bool SIDE_BOTTOM = false;
const bool SIDE_TOP = true;
const bool ANIM_IN = false;
const bool ANIM_OUT = true;
const byte CHARACTER_LEFT = 0;
const byte CHARACTER_RIGHT = 1;
const byte TEXTBOX = 2;

struct animationPos_t {
  uint16_t currentTime;
  const uint8_t *bitmap;
  bool side;
  bool inOut;
  bool finished;
};

class Cutscene
{
  public:
    Cutscene();
    void show(byte cutsceneId);
    boolean loop();
  private:
    animationPos_t animationElements[3];
    boolean waitForButton(int n);
    void updateCharacterAnims();
    void updateCharacterAnim(animationPos_t* element);
    void updateTextboxAnim();
    void drawCharacter(int16_t xPos, const uint8_t *bitmap, bool flipped);
    void drawTextbox(int16_t yPos, const uint8_t *bitmap);
    float easeIn(float currentTime, float startValue, float changeInValue, float duration);
    float easeOut(float currentTime, float startValue, float changeInValue, float duration);
};

#endif
