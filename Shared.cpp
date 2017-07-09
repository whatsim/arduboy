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
