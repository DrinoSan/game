#pragma once
#include <string>

#include "TextureStore.h"
#include "raylib.h"

enum class Facing_t
{
   UP,
   RIGHT,
   DOWN,
   LEFT
};

enum class Activity_t
{
   Idle,
   Walk,
   Attack,
   Hurt,
   Die
};

enum class AnimId
{
   WalkFront,
   WalkBack,
   WalkLeft,
   WalkRight,
   Count,
   /* Idle, Attack later */
};

struct Animation_t
{
   TextureIndex textureIndex;
   int          frameWidth;
   int          frameHeight;
   int          frameCount;
   float        frameDuration;
};
