#pragma once
#include "raylib.h"

enum class AnimId { WalkFront, WalkBack, WalkLeft, WalkRight, /* Idle, Attack later */ Count };

struct Animation_t
{
   Texture2D texture;
   int       frameWidth;      // 32
   int       frameHeight;     // 32
   int       frameCount;      // 8
   float     frameDuration;   // 0.1s
};

struct AnimationChoice_t
{
   Animation_t* animation;
   bool         flip;
};
