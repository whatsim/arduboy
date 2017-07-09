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

  Sprites::drawSelfMasked(20,20,sprite_platform,0);
  Sprites::drawSelfMasked(27,20,sprite_platform,0);

  Typewriter::numAt(0,0,round(millis()/1000));
  
  return mode;
}

