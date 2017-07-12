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
  if(x >= 0 && y >= 0 && x < map_one[0] && y < map_one[1]){
    int x8 = floor(x / 2);
    char mapByte = pgm_read_byte(&map_one[2 + x8 + y * map_one[0]/2]);
    if(x % 2 == 1) mapByte = mapByte >> 4;
    
    return mapByte & 15;
  } else {
    return 0;
  }
}

Shared::FPoint Shared::speedAfterMapCollision(FPoint position, FPoint speed){
  int xCoord = ceil(position.x/16)*16;
  int yCoord = ceil(position.y/16)*16; // 8 is the height of the spider
  int tileID = getTile(position.x + speed.x,position.y - speed.y,true);

  if(tileID > 6){
    // is there a tile where you are going
    if(speed.y < 0){
      // are you falling
      if(position.y <= yCoord){
        // is where you were above the tile
        speed.y = abs(position.y - yCoord) < abs(speed.y) ? position.y - yCoord : speed.y;
        Serial.println("xxx");
        Serial.println(yCoord);
        Serial.println(position.y);
//        speed.y = speed.y > 0 ? 0 : speed.y;
      }
    }
  }
  
  return speed;
}


