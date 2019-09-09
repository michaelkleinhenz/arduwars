#include "Arduboy2.h"
#include "globals.h"
#include "bitmaps.h"  
#include "cutscene.h"
#include "font4x6.h"

Font4x6 font4x6 = Font4x6();
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

Cutscene::Cutscene() {
}

// waits for button or given timeout
boolean Cutscene::waitForButton(int n) {
  for(int i = 0; i < n; i++) {
    delay(15);
    byte pad = arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON);
    if (pad==1) {
      return true;
    }
  }
  return false;
}

void Cutscene::drawCharacter(int16_t xPos, const uint8_t *bitmap, bool flipped) {
  ardbitmap.drawBitmap(xPos, 0, bitmap, 64, 64, WHITE, ALIGN_NONE, flipped?MIRROR_HORIZONTAL:MIRROR_NONE);  
}

void Cutscene::drawTextbox(int16_t yPos, const uint8_t *bitmap) {
  sprites.drawOverwrite(15, yPos, bitmap, 0);
  font4x6.setCursor(19, 39);
  font4x6.print(F("ABCDEFGHIJKLMNOPQR"));
  font4x6.print(F("\nabcdefghijklmnopqr"));
  font4x6.print(F("\nABCDEFGHIJKLMNOPQR"));
  //arduboy.display();
}

void Cutscene::show(byte cutsceneId) {
  // add animationElements
  animationPos_t element;
  element.bitmap = character_01_normal;
  element.currentTime = 0;
  element.finished = false;
  element.inOut = ANIM_IN;
  element.side = SIDE_RIGHT;
  animationElements[CHARACTER_LEFT] = element;
  animationPos_t textbox;
  textbox.bitmap = textbox_normal;
  textbox.currentTime = 0;
  textbox.finished = false;
  textbox.inOut = ANIM_IN;
  textbox.side = SIDE_TOP;
  animationElements[TEXTBOX] = textbox;
}

float Cutscene::easeIn(float currentTime, float startValue, float changeInValue, float duration) {
  currentTime /= duration;
  return -changeInValue * currentTime * (currentTime-2) + startValue;  
}

float Cutscene::easeOut(float currentTime, float startValue, float changeInValue, float duration) {
  currentTime /= duration;
  return changeInValue * currentTime * currentTime + startValue;  
}

void Cutscene::updateCharacterAnim(animationPos_t* element) {
  float currentXPos = (element->side==SIDE_LEFT)?0:64;
  float startValue = 0;
  float changeInValue = 0;
  if (element->inOut==ANIM_IN) {
    startValue = (element->side==SIDE_LEFT)?-64:128;
    changeInValue = (element->side==SIDE_LEFT)?64:-64;
  } else {
    startValue = (element->side==SIDE_LEFT)?0:64;
    changeInValue = (element->side==SIDE_LEFT)?-64:64;
  }
  if (element->currentTime>=ANIM_SPEED) {
    element->finished = true;
  }
  if (!element->finished) {
    if (element->inOut==ANIM_IN) {
      currentXPos = easeIn(element->currentTime, startValue, changeInValue, ANIM_SPEED);
    } else {
      currentXPos = easeOut(element->currentTime, startValue, changeInValue, ANIM_SPEED);
    }
  } 
  drawCharacter(currentXPos, element->bitmap, (element->side==SIDE_LEFT)?false:true);
  element->currentTime++;
}

void Cutscene::updateCharacterAnims() {
  updateCharacterAnim(&animationElements[CHARACTER_LEFT]);
  updateCharacterAnim(&animationElements[CHARACTER_RIGHT]);
}

void Cutscene::updateTextboxAnim() {
  animationPos_t* textbox = &animationElements[TEXTBOX];
  float currentYPos = 37;
  float startValue = 0;
  float changeInValue = 0;
  if (textbox->inOut==ANIM_IN) {
    startValue = 64;
    changeInValue = -27;
  } else {
    startValue = 37;
    changeInValue = 27;
  }
  if (textbox->currentTime>=ANIM_SPEED) {
    textbox->finished = true;
  }
  if (!textbox->finished) {
    if (textbox->inOut==ANIM_IN) {
      currentYPos = easeIn(textbox->currentTime, startValue, changeInValue, ANIM_SPEED);
    } else {
      currentYPos = easeIn(textbox->currentTime, startValue, changeInValue, ANIM_SPEED);
    }
  }
  drawTextbox(currentYPos, textbox->bitmap);
  textbox->currentTime++;
}

// cutscene loop, returns true as long as cutscene is running
boolean Cutscene::loop() {
  //waitForButton(100);
  arduboy.clear();
  //return false;
  updateCharacterAnims();
  updateTextboxAnim();
  /*
  if (animationElements[0].finished) {
    animationElements[0].finished = false;
    animationElements[0].inOut = ANIM_OUT;
    animationElements[0].currentTime = 0;
  }
  */
  arduboy.display();
  return true;
}
