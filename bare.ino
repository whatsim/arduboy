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
//  arduboy.begin();
  arduboy.boot(); // raw hardware
  arduboy.blank(); // blank the display
  arduboy.audio.begin();

  // here we set the framerate to 30, we do not need to run at default 60 and
  // it saves us battery life.
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
