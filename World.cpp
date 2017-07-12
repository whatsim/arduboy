/*
  World.cpp
*/

#include "World.h"

World::World()
{
  Spider spider = Spider();
  
}

Shared::Gamemode World::loop(Arduboy2 arduboy,ArduboyTones sounds)
{
  Shared::Gamemode mode = Shared::world;

  if(arduboy.pressed(LEFT_BUTTON)){
    spider.xSpeed -= spider.horSpeed;
    if(abs(spider.xSpeed) > spider.horSpeed) spider.xSpeed = -spider.horSpeed;
  }  
  if(arduboy.pressed(RIGHT_BUTTON)){
    spider.xSpeed += spider.horSpeed;
    if(spider.xSpeed > spider.horSpeed) spider.xSpeed = spider.horSpeed;
  }

  if(arduboy.pressed(DOWN_BUTTON) && arduboy.justPressed(B_BUTTON) && spider.canJump){
    spider.y ++;
  } else if(arduboy.justPressed(B_BUTTON) && spider.canJump){
    spider.ySpeed = 6;
    sounds.tone(NOTE_C2,100);
  }
  if(arduboy.justReleased(B_BUTTON) && spider.ySpeed > 0) spider.ySpeed = 0;

  if(spider.y > 255){
    spider.health --;
    spider.x = spider.lastGroundX;
    spider.y = spider.lastGroundY;
  }
  
  Point spiderPos = spider.update(sounds);
  updateCameraPos(spiderPos);
  renderWorld();
  spider.draw(arduboy,cameraPos);
  
  for(int i = 0; i < Shared::maxHealth; i++){
    int frame = i > spider.health - 1 ? 1 : 0;
    Sprites::drawSelfMasked(0 + i * 6,0,sprite_heart,frame);  
  }
  
  
  return mode;
}

void World::updateCameraPos(Point pos){
  if(pos.x - cameraPos.x > 80){
    cameraPos.x = pos.x - 80;
  }
  if(pos.x - cameraPos.x < 44){
    cameraPos.x = pos.x - 44;
  }
  if(pos.y - cameraPos.y > 48){
    cameraPos.y = pos.y - 48;
  }
  if(pos.y - cameraPos.y < 30){
    cameraPos.y = pos.y - 30;
  }
}

void World::renderWorld(){
  for(int x = 1; x < map_one[0]; x ++){
    for(int y = 1; y < map_one[1]; y ++){
      int tile = Shared::getTile(x,y,false);
      
      Sprites::drawSelfMasked(x * 16 - cameraPos.x,y*16 - cameraPos.y,sprite_tiles,tile);
      
    }
  }
}

