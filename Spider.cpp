/*
  Spider.cpp
*/

#include "Spider.h"

Spider::Spider()
{
  
}

void Spider::update()
{
  x += xSpeed * xSpeedMult;
  y -= ySpeed * ySpeedMult;
  
  if(y >= 64){
    y = 64;
    ySpeed = 0;
    canJump = true;
  } else {
    ySpeed -= 1;
    canJump = false;
  }
  
  
  currentMode = idling;
  if(ySpeed == 0 && xSpeed != 0){
    currentMode = running;
  }
  if(ySpeed != 0 || y != 64){
    currentMode = jumping;
  }
}

void Spider::draw(Arduboy2 arduboy)
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
    Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderLeft,frame);
  } else {
    Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderRight,frame);
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
  return frame;
}

int Spider::continueJumping(Arduboy2 arduboy){
  int frame = ySpeed > -1 ? jumpFrame : fallFrame;

  return frame;
}

void Spider::startIdling(Arduboy2 arduboy){
  frameCounter = 0;
  startFrame = arduboy.frameCount + 7;
  edgeMode = lastMode;
}
int Spider::continueIdling(Arduboy2 arduboy){

  int frame = frameCounter;
  if(edgeMode != idling){
    frame = edgeMode == jumping ? 9 : 3;
  }
  if ((arduboy.frameCount - startFrame) % idleFrameDelay == 0) frameCounter += 1;
  if(frameCounter == 1) edgeMode = idling;
  frameCounter = frameCounter % numIdleFrames;
  return frame;
}


