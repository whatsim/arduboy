/*
  Spider.h
*/
#ifndef Spider_h
#define Spider_h

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Assets.h"
#include "Shared.h"

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
    void draw(Arduboy2 arduboy, Point cameraPos);
    Point update(ArduboyTones sounds);
    
    float x = 36;
    float y = 0;
    float xSpeed = 0;
    float ySpeed = 0;
    
    int health = 3;
    bool canJump = true;

    const int spriteCenterX = 13;
    const int spriteCenterY = 9;
  private:
    Spidermode currentMode = idling;
    Spidermode lastMode = idling;
    Spidermode edgeMode = idling;
    
    void startRunning(Arduboy2 arduboy);
    int continueRunning(Arduboy2 arduboy);
    int continueJumping(Arduboy2 arduboy);
    void startIdling(Arduboy2 arduboy);
    int continueIdling(Arduboy2 arduboy);
    
    const int startRunFrame = 3;
    const int numRunFrames = 3;
    const int runFrameDelay = 6;
    const int skidFrame = 3;
    
    const int jumpFrame = 7;
    const int fallFrame = 8;
    const int smashFrame = 9;
    
    const int numIdleFrames = 3;
    const int idleFrameDelay = 20;
    
    const int xSpeedMult = 3;
    const int ySpeedMult = 1;
    
    int frameCounter = 0;
    int lastDirection = 1;
    int startFrame = 0;

};

#endif
