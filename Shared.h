/*
  Shared.h
*/
#ifndef Shared_h
#define Shared_h

#include <Arduboy2.h>

namespace Shared
{
    float lerp(float a, float b, float f);
    void shuffle(int *array, size_t n);
    typedef enum Gamemode {
  	  title,
  	  menu,
  	  scanner,
      router,
      hacker,
      success,
      error,
      dice
  	};
};

#endif
