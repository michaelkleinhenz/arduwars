#ifndef INTRO_H
#define INTRO_H

class Intro
{
  public:
    Intro();
    void show();
    boolean loop();
  private:
    boolean waitForButton(int n);
};

#endif
