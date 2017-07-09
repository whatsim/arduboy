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
  } else {
    ySpeed -= 1;
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
  switch (currentMode){
    case running:
      if(currentMode == lastMode){
        continueRunning(arduboy);
      } else {
        startRunning(arduboy);
      }
    break;
    case jumping:
      if(currentMode == lastMode){
        continueJumping(arduboy);
      } else {
        startJumping(arduboy);
      }
    break;
    case idling:
      if(currentMode == lastMode){
        continueIdling(arduboy);
      } else {
        startIdling(arduboy);
      }
    break;
  }
  lastMode = currentMode;
  if(xSpeed != 0) lastDirection = xSpeed/abs(xSpeed);
}

void Spider::startRunning(Arduboy2 arduboy){
  frameCounter = 0;
  continueRunning(arduboy);
  
}
void Spider::continueRunning(Arduboy2 arduboy){
  if(lastDirection < 0){
    Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderLeft,startRunFrame + frameCounter);
  } else {
    Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderRight,startRunFrame + frameCounter);
  }
  if (arduboy.frameCount % runFrameDelay == 0) frameCounter += 1;
  frameCounter %= numRunFrames;

}

void Spider::startJumping(Arduboy2 arduboy){
  continueJumping(arduboy);
}
void Spider::continueJumping(Arduboy2 arduboy){
  int frame = ySpeed > -1 ? jumpFrame : fallFrame;

  if(lastDirection < 0){
    Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderLeft,frame);
  } else {
    Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderRight,frame);
  }
}

void Spider::startIdling(Arduboy2 arduboy){
  frameCounter = 0;
  startFrame = arduboy.frameCount + idleFrameDelay / 4;
  edgeMode = lastMode;
  continueIdling(arduboy);
}
void Spider::continueIdling(Arduboy2 arduboy){

  if(edgeMode == idling){
    if(lastDirection < 0){
      Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderLeft,frameCounter);
    } else {
      Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderRight,frameCounter);
    }
  } else {
    int frame = edgeMode == jumping ? 9 : 3;
    if(lastDirection < 0){
      Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderLeft,frame);
    } else {
      Sprites::drawPlusMask(x - spriteCenterX,y - spriteCenterY,sprite_spiderRight,frame);
    }
  }
  if ((arduboy.frameCount - startFrame) % idleFrameDelay == 0) frameCounter += 1;
  if(frameCounter == 1) edgeMode = idling;
  frameCounter = frameCounter % numIdleFrames;
  
}


