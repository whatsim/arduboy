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

  spider.xSpeed *= 0.8;
  if(abs(spider.xSpeed) < 0.1) spider.xSpeed = 0;
  if(arduboy.pressed(LEFT_BUTTON)){
    spider.xSpeed -= 1;
    if(spider.xSpeed < -1) spider.xSpeed = -1;
  }  
  if(arduboy.pressed(RIGHT_BUTTON)){
    spider.xSpeed += 1;
    if(spider.xSpeed > 1) spider.xSpeed = 1;
  }

  if(arduboy.justPressed(B_BUTTON) && spider.canJump){
    spider.ySpeed = 8;
  }
  if(arduboy.justReleased(B_BUTTON) && spider.ySpeed > 0) spider.ySpeed = 0;
  if(arduboy.justPressed(B_BUTTON)){
    sounds.tone(NOTE_C2,100);
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
  if(pos.y - cameraPos.y > 52){
    cameraPos.y = pos.y - 52;
  }
  if(pos.y - cameraPos.y < 30){
    cameraPos.y = pos.y - 30;
  }
}

void World::renderWorld(){
  for(int x = 0; x < map_one[0]; x ++){
    for(int y = 0; y < map_one[1]; y ++){
      int tile = Shared::getTile(x,y,false);
      if(tile != 0){
        Sprites::drawSelfMasked(x * 16 - cameraPos.x,y*16 - cameraPos.y,sprite_platform,tile-1);
      }
    }
  }
}
