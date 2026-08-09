#pragma once

#include "TextureStore.h"

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
   Idle,
   Count,
   /* Attack later */
};

struct Animation_t
{
   TextureIndex textureIndex;
   int          frameWidth;
   int          frameHeight;
   int          frameCount;
   float        frameDuration;
};
