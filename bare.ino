#include <Arduboy2.h>
#include <ArduboyTones.h>

#include "Shared.h"
#include "Assets.h"

// modes
#include "World.h"

// Make an instance of arduboy used for many functions
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

World world = World();

Shared::Gamemode mode = Shared::world;

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
    case Shared::world:
      mode = world.loop(arduboy);
    break;
  }

  arduboy.display();
  arduboy.idle();
}
