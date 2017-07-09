/*
  World.h
*/
#ifndef World_h
#define World_h

#include <Arduboy2.h>
#include "Shared.h"
#include "Assets.h"
#include "Typewriter.h"
#include "Spider.h"

class World
{
  public:
    World();
    Shared::Gamemode loop(Arduboy2 arduboy);
  private:
    Spider spider;
};

#endif
