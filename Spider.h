/*
  Spider.h
*/
#ifndef Spider_h
#define Spider_h

#include <Arduboy2.h>
#include "Assets.h"

class Spider
{
  public:
    Spider();
    typedef enum Spidermode {
      running,
      jumping,
      falling,
      idling
    };
    void draw(Arduboy2 arduboy);
    void update();
    
    float x = 0;
    float y = 0;
    float xSpeed = 0;
    float ySpeed = 0;
    
    int health = 3;
  private:
    Spidermode currentMode = idling;
    Spidermode lastMode = idling;
    Spidermode edgeMode = idling;
    
    void startRunning(Arduboy2 arduboy);
    void continueRunning(Arduboy2 arduboy);
    void startJumping(Arduboy2 arduboy);
    void continueJumping(Arduboy2 arduboy);
    void startIdling(Arduboy2 arduboy);
    void continueIdling(Arduboy2 arduboy);
    
    const int startRunFrame = 3;
    const int numRunFrames = 3;
    const int runFrameDelay = 6;
    
    const int jumpFrame = 7;
    const int fallFrame = 8;
    
    const int numIdleFrames = 3;
    const int idleFrameDelay = 20;
    
    const int spriteCenterX = 13;
    const int spriteCenterY = 8;
    
    const int xSpeedMult = 5;
    const int ySpeedMult = 1;
    
    int frameCounter = 0;
    int lastDirection = 1;
    int startFrame = 0;
};

#endif
