/*
  World.cpp
*/

#include "World.h"

World::World()
{
  Spider spider = Spider();
  
  spider.x = 13;
}

Shared::Gamemode World::loop(Arduboy2 arduboy)
{
  Shared::Gamemode mode = Shared::world;

  spider.xSpeed *= 0.8;
  if(abs(spider.xSpeed) < 0.1) spider.xSpeed = 0;
  if(arduboy.pressed(LEFT_BUTTON)){
    spider.xSpeed += -1;
    if(spider.xSpeed < -1) spider.xSpeed = -1;
  }  
  if(arduboy.pressed(RIGHT_BUTTON)){
    spider.xSpeed += 1;
    if(spider.xSpeed > 1) spider.xSpeed = 1;
  }
  if(arduboy.justPressed(B_BUTTON) && spider.canJump){
    spider.ySpeed = 6;
  }
  
  spider.update();
  spider.draw(arduboy);
  
  return mode;
}

