#pragma once
#include <string>

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
   Texture2D texture;
   int       frameWidth;      // 32
   int       frameHeight;     // 32
   int       frameCount;      // 8
   float     frameDuration;   // 0.1s

   Animation_t( const std::string texturePath )
   {
      frameCount    = 8;
      frameDuration = 0.1f;
      texture       = LoadTexture( texturePath.c_str() );
      frameWidth    = texture.width / frameCount;
      frameHeight   = texture.height;
   }

   Animation_t() = default;
};
