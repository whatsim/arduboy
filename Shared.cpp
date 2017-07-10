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
  if(x > 0 && y > 0 && x/2 * y < sizeof(map_one)){
    int x8 = floor(x / 2);
    char mapByte = pgm_read_byte(&map_one[x8 + y * 8]);
    if(x % 2 == 1) mapByte = mapByte >> 4;
    return mapByte & 15;
  } else {
    return 0;
  }
}

int Shared::getTileTop(int x, float y){
  y = round((y - 1) / 16);
  x /= 16;
  int intY = (int)y;
  if(x > 0 && y > 0 && x/2 * y < sizeof(map_one)){
    int x8 = floor(x / 2);
    char mapByte = pgm_read_byte(&map_one[x8 + intY  * 8]);
    if(x % 2 == 1) mapByte = mapByte >> 4;
    return mapByte & 15;
  } else {
    return 0;
  }
}

