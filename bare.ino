#include <Arduboy2.h>
#include <ArduboyTones.h>

#include "Shared.h"
#include "Assets.h"

// modes
#include "Dice.h"

// Make an instance of arduboy used for many functions
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Dice dice = Dice();

Shared::Gamemode mode = Shared::dice;

void setup() {
  
  //initiate arduboy instance
  arduboy.boot(); 
  arduboy.blank(); 
  arduboy.audio.begin();
  arduboy.setFrameRate(30);

}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();

  switch (mode){
    case Shared::dice:
      mode = dice.loop(arduboy);
    break;
  }

  arduboy.display();
  arduboy.idle();
}
