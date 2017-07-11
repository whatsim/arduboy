/*
  Shared.h
*/
#ifndef Shared_h
#define Shared_h

#include <Arduboy2.h>
#include "Assets.h"

namespace Shared
{
    float lerp(float a, float b, float f);
    void shuffle(int *array, size_t n);
    typedef enum Gamemode {
  	  world
  	};
    const int maxHealth = 3;
    int getTile(int x, int y, bool world);
    Point speedAfterMapCollision(Point position, Point speed);
};

#endif
