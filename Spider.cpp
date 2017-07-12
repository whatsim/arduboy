/*
  Spider.cpp
*/

#include "Spider.h"

Spider::Spider()
{
  
}

Point Spider::update(ArduboyTones sounds)
{

  ySpeed -= 1;
  Shared::FPoint s = Shared::speedAfterMapCollision({x:x,y:y},{x:xSpeed,y:ySpeed});

  xSpeed = s.x;
  ySpeed = s.y;

  bool tileBelow = ySpeed == 0 && Shared::getTile(x,y,true) != 0;

  x += xSpeed;
  y -= ySpeed;
  
  if(tileBelow){
    if(!canJump){
      sounds.tone(NOTE_C1,100);
    }
    xSpeed *= 0.9;
    if(abs(xSpeed) < 0.1) xSpeed = 0;
    canJump = true;
  } else {
    
    ySpeed = ySpeed > -10 ? ySpeed : -10;
    canJump = false;
  }
  
  
  currentMode = idling;
  if(ySpeed == 0 && xSpeed != 0){
    currentMode = running;
  }
  if(ySpeed != 0 || !tileBelow){
    currentMode = jumping;
  }

  // return position to world
  return Point{x,y};
}

void Spider::draw(Arduboy2 arduboy, Point cameraPos)
{
  int frame = 0;
  switch (currentMode){
    case running:
      if(currentMode != lastMode){
        startRunning(arduboy);
      }
      frame = continueRunning(arduboy);
    break;
    case jumping:
      frame = continueJumping(arduboy);
    break;
    case idling:
      if(currentMode != lastMode){
        startIdling(arduboy);
      }
      frame = continueIdling(arduboy);
    break;
  }

  if(lastDirection < 0){
    Sprites::drawPlusMask(x - cameraPos.x - spriteCenterX,y - cameraPos.y - spriteCenterY,sprite_spiderLeft,frame);
  } else {
    Sprites::drawPlusMask(x - cameraPos.x - spriteCenterX,y - cameraPos.y - spriteCenterY,sprite_spiderRight,frame);
  }
  
  lastMode = currentMode;
  if(xSpeed != 0) lastDirection = xSpeed/abs(xSpeed);
}

void Spider::startRunning(Arduboy2 arduboy){
  frameCounter = 0;
  
}
int Spider::continueRunning(Arduboy2 arduboy){
  int frame = startRunFrame + frameCounter;
  if (arduboy.frameCount % runFrameDelay == 0) frameCounter += 1;
  frameCounter %= numRunFrames;
  if(arduboy.notPressed(LEFT_BUTTON | RIGHT_BUTTON)){
    frame = skidFrame;
  }
  return frame;
}

int Spider::continueJumping(Arduboy2 arduboy){
  int frame = ySpeed > -1 ? jumpFrame : fallFrame;

  return frame;
}

void Spider::startIdling(Arduboy2 arduboy){
  frameCounter = 0;
  startFrame = arduboy.frameCount + 8;
  edgeMode = lastMode;
}
int Spider::continueIdling(Arduboy2 arduboy){

  int frame = frameCounter;
  if(edgeMode != idling){
    frame = edgeMode == jumping ? smashFrame : skidFrame;
  }
  if ((arduboy.frameCount - startFrame) % idleFrameDelay == 0) frameCounter += 1;
  if(frameCounter == 1) edgeMode = idling;
  frameCounter = frameCounter % numIdleFrames;
  return frame;
}



