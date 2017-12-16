#ifndef CUTSCENE_H
#define CUTSCENE_H

class Cutscene
{
  public:
    Cutscene();
    void show(byte cutsceneId);
    boolean loop();
};

#endif
