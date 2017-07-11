/*
  Shared.cpp
*/

#include "Shared.h"

float Shared::lerp(float a, float b, float f)
{
    return a + f * (b - a);
}
void Shared::shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
int Shared::getTile(int x, int y, bool world){
  if(world){
    x = x / 16;
    y = y / 16;
  }
  if(x > 0 && y > 0 && x < map_one[0] && y < map_one[1]){
    int x8 = floor(x / 2);
    char mapByte = pgm_read_byte(&map_one[2 + x8 + y * map_one[0]/2]);
    if(x % 2 == 1) mapByte = mapByte >> 4;
    
    return mapByte & 15;
  } else {
    return 0;
  }
}

Point Shared::speedAfterMapCollision(Point position, Point speed){
  int xCoord = floor(position.x + speed.x);
  int yCoord = floor(position.y + speed.y + 8); // 8 is the height of the spider
  int tileID = getTile(xCoord,yCoord,false);
  // should check if tileid allows a given direction of movement
  // right now i only have platforms, and not other kinds of tile,
  // so assuming it resists position y speed is enough.
  if(tileID != 0){
    if(speed.y > 0){
      speed.y = yCoord - position.y;
    }
  }
  // may not return fractional speed, need to make a float point?
  return speed;
}

