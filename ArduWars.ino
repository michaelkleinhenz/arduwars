/* 
 * ArduWars - A Strategy Game for Arduboy
 * Copyright (C) 2017 Michael Kleinhenz <michael@kleinhenz.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "pins_arduino.h" // Arduino pre-1.0 needs this
#include "Arduboy2.h"
#include "Sprites.h"

#include "globals.h"
#include "bitmaps.h"
#include "intro.h"
#include "battle.h"
#include "menu.h"
#include "cutscene.h"

// declare globals
Arduboy2 arduboy;
Sprites sprites;

// declare screens
Intro intro;
Battle battle;
Menu menu;
Cutscene cutscene;

// declare locals
boolean inIntro = false;
boolean inBattle = false;
boolean inCutscene = false;
byte selectedMenuItem = -1;

// displays the intro
void showIntro() {
  inIntro = true;
  intro.show();
}

// shows a battle
void showBattle(byte mapId) {
  inBattle = true;
  battle.show(0);
}

// shows a cutscene
void showCutscene(byte cutsceneId) {
  inCutscene = true;
  cutscene.show(0);
}

// shows the main menu
void showMenu() {
  selectedMenuItem = -1;
  menu.show();
}

// built-in: setup application
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.display();
  // init the debugging
  Serial.begin(9600);
  // we always start with the intro
  showIntro();
}

// built-in: main game loop
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // main loop, delegate to the active screen
  if (inIntro) {
    inIntro = intro.loop();
    if (!inIntro) {
      // after the intro, we start the battle (for now)
      //showBattle(0);
      showCutscene(0);
    }
    return;    
  } else if (inBattle) {
    inBattle = battle.loop();
    return;    
  } else if (inCutscene) {
    inCutscene = cutscene.loop();
    return;    
  } else if (selectedMenuItem == -1) {
    selectedMenuItem = menu.loop();
    if (selectedMenuItem == 0) {
      // some menu item was selected 
      showBattle(0);
    }
    return;
  }
}


