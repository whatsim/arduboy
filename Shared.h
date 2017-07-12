/*
  Shared.h
*/
#ifndef Shared_h
#define Shared_h

#include <Arduboy2.h>
#include "Assets.h"

namespace Shared
{
    const int maxHealth = 3;
    float lerp(float a, float b, float f);
    void shuffle(int *array, size_t n);
    int getTile(int x, int y, bool world);
    
    typedef enum Gamemode {
  	  world
  	};
    struct FPoint {
        float x; 
        float y;
    };  
    FPoint speedAfterMapCollision(FPoint position, FPoint speed);
};

#endif

