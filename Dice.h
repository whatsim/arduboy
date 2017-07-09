/*
  Dice.h
*/
#ifndef Dice_h
#define Dice_h

#include <Arduboy2.h>
#include "Shared.h"
#include "Assets.h"
#include "Typewriter.h"

class Dice
{
  public:
    Dice();
    Shared::Gamemode loop(Arduboy2 arduboy);
    int result = 0;
  private:
    int roll();
    int numDice = 1;
    int rolledDice = 1;
    int numSides = 5;
    int plus = 0;
    int diceResults[20] = {0};
    int cursorPos = 0;
    int upDownRepeat = 0;
    char buf[8];
    Arduboy2 &arduboy;
};

#endif
