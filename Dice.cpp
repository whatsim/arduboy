/*
  Dice.cpp
*/

#include "Dice.h"

Dice::Dice()
{
  
}

Shared::Gamemode Dice::loop(Arduboy2 arduboy)
{
  Shared::Gamemode mode = Shared::dice;

  if (arduboy.justPressed(LEFT_BUTTON)) {
    cursorPos --;
    upDownRepeat = 0;
  }
  if (arduboy.justPressed(RIGHT_BUTTON)) {
    cursorPos ++;
    upDownRepeat = 0;
  }
  if (arduboy.justPressed(B_BUTTON)) {
    arduboy.initRandomSeed();
    result = roll();
  }

  if(result != 0){
    itoa(result,buf,10);
    Typewriter::textAt(100,16,"TOTAL");
    Typewriter::textAt(100,25,buf);
    int x = 2;
    int y = 37;
    for(int i = 0; i < rolledDice; i++){
      itoa(diceResults[i],buf,10);
      x += Typewriter::textAt(x,y,buf) * 5 + 5; 
      if(x > 100){
        x = 2;
        y += 9;
      }
    }
  } else {
    rolledDice = 0;
  }

  if(arduboy.justReleased(UP_BUTTON | DOWN_BUTTON) || arduboy.justPressed(UP_BUTTON | DOWN_BUTTON)){
    upDownRepeat = 0;
  }

  if(upDownRepeat == 0){
    if (arduboy.pressed(UP_BUTTON)) {
      if(cursorPos == 0){
        numDice ++;
      }
      if(cursorPos == 1){
        numSides ++;
      }
      if(cursorPos == 2){
        plus ++;
      }
    }
    if (arduboy.pressed(DOWN_BUTTON)) {
      if(cursorPos == 0){
        numDice --;
      }
      if(cursorPos == 1){
        numSides --;
      }
      if(cursorPos == 2){
        plus --;
      }
    }
    numDice += 20;
    numDice %= 20;
    numSides += 100;
    numSides %= 100;
    plus += 100;
    plus %= 100;
    upDownRepeat = 5;
  }

  if(upDownRepeat > 0){
    upDownRepeat--;
  }

  cursorPos += 3;
  cursorPos %= 3;

  itoa(numDice + 1,buf,10);
  int diceLength = Typewriter::textAt(2,25,buf);
  Typewriter::textAt(5 + 5 * diceLength,25,"D");
  itoa(numSides+1,buf,10);
  int sidesLength = Typewriter::textAt(13 + 5 * diceLength,25,buf);
  itoa(plus,buf,10);
  int plusLength = Typewriter::textAt(23 + 5 * diceLength + 5 * sidesLength,25,buf);
  

  //plus sign
  arduboy.drawFastHLine(16 + 5 * diceLength + 5 * sidesLength, 28, 5);
  arduboy.drawFastVLine(18 + 5 * diceLength + 5 * sidesLength, 26, 5);

  if(cursorPos == 0){
    arduboy.drawFastHLine(2, 33, 5 * diceLength + 1);
  }
  if(cursorPos == 1){
    arduboy.drawFastHLine(13 + 5 * diceLength, 33, 5 * sidesLength  + 1);
  }
  if(cursorPos == 2){
    arduboy.drawFastHLine(23 + 5 * diceLength + 5 * sidesLength , 33, 5 * plusLength + 1);
  }

  Sprites::drawSelfMasked(109,55,sprite_confirm,0);
  
  return mode;
}

int Dice::roll(){
  int out = 0;
  rolledDice = numDice + 1;
  for(int i = 0; i < numDice + 1; i++){
    diceResults[i] = random(1,numSides+2);
    out += diceResults[i];
  }
  return out + plus;
}

