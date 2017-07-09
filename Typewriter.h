/*
  Typewriter.h
*/
#ifndef Typewriter_h
#define Typewriter_h

#include <Arduboy2.h>
#include "Assets.h"

namespace Typewriter {
  int textAt(int x,int y,char* string);
  void numAt(int x,int y,int digit);
}

#endif
