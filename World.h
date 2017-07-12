/*
  World.h
*/
#ifndef World_h
#define World_h

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Shared.h"
#include "Assets.h"
#include "Typewriter.h"
#include "Spider.h"

class World
{
  public:
    World();
    Shared::Gamemode loop(Arduboy2 arduboy, ArduboyTones sound);
  private:
    void updateCameraPos(Point pos);
    Spider spider;
    Point cameraPos = Point();
    void renderWorld();
    
};

#endif

